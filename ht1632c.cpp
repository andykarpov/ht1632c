#include <avr/io.h> 
#include <avr/wdt.h>
#include <avr/pgmspace.h> 
#include <Arduino.h>
#include "ht1632c_font.h"
#include "ht1632c.h"
#include "digitalWriteFast.h"

#undef abs
#include <stdlib.h>

/******************************************************************************
 * Constructors
 ******************************************************************************/

/**
 * Constructor for one display panel
 * 
 */
ht1632c::ht1632c()
{
	set_display_geometry(HT1632_GEOMETRY_X, HT1632_GEOMETRY_Y);
	setup(HT1632_DATA_PIN, HT1632_WRCLK_PIN, 1);
}

/******************************************************************************
 * public API
 ******************************************************************************/

/**
 * Plot a dot
 *
 * @param char x
 * @param char y
 * @param char val
 */
void ht1632c::plot (char x, char y, char val) {
  
  char addr, bitval;
 
  if (x<0 || x > _geometry_x-1 || y < 0 || y > _geometry_y-1) return;

  byte d = x / _geometry_x;
  x = x - _geometry_x*d;

  /*
   * The 4 bits in a single memory word go DOWN, with the LSB (first transmitted) bit being on top.  However, writebits()
   * sends the MSB first, so we have to do a sort of bit-reversal somewhere.  Here, this is done by shifting the single bit in
   * the opposite direction from what you might expect.
   */

  bitval = 8>>(y&3);  // compute which bit will need set

  addr = (x<<2) + (y>>2);  // compute which memory word this is in 

  if (val) {  // Modify the shadow memory
    _shadowram[(d * 96)  + addr] |= bitval;
  } 
  else {
    _shadowram[(d * 96) + addr] &= ~bitval;
  }
  // Now copy the new memory value to the display
  if (_direct_write) {
  	senddata(d, addr, _shadowram[(d * 96) + addr]);
  }
}

void ht1632c::clear() {
	char i;
	for(byte d=0; d<_displays; d++)
	{
		chipselect(HT1632_CS_PIN);  // Select chip
		writebits(HT1632_ID_WR, 1<<2);  // send ID: WRITE to RAM
		writebits(0, 1<<6); // Send address
		for (i = 0; i < 96/2; i++) // Clear entire display
			writebits(0, 1<<7); // send 8 bits of data
		chipfree(HT1632_CS_PIN); // done
		for (i=0; i < 96; i++)
			_shadowram[96*d + i] = 0;
	}
}

void ht1632c::set_font(byte width, byte height) {
	_font_width = width;
	_font_height = height;
}

void ht1632c::put_char(byte x, byte y, char c) {
  byte dots;
  c = c - 32; // offset
  if (_font_height <= 8) {
	for (char col=0; col< _font_width; col++) {
		switch (_font_width) {
		case 3:
			dots = pgm_read_byte_near(&ht1632c_font_3x5[c][col]);
		break;
		case 4:
			dots = pgm_read_byte_near(&ht1632c_font_4x7[c][col]); 
		break;
		case 5:
			dots = pgm_read_byte_near(&ht1632c_font_5x7[c][col]);
		break;
		}
    	for (char row=0; row < _font_height; row++) {
      		if (bitRead(dots, 7-row))
        		plot(x+col, y+row, 1);
      		else 
        		plot(x+col, y+row, 0);
    	}
  	}
  } else {
	for (byte row=0; row < _font_height; row++)
	{
		dots = pgm_read_byte_near(&ht1632c_font_5x12[c][row]);
		for (byte col=0; col<_font_width; col++)
		{
			if (bitRead(dots, 7-col))
				plot(x+col, y+row, 1);
			else 
				plot(x+col, y+row, 0);
		}
	}
  }
}

void ht1632c::putstring(byte x, byte y, char* c) {
	byte i =0;
	while(c[i]) {
		put_char(x,y, c[i]);
		x = x + _font_width + 1;
		i++;
	}
}

void ht1632c::flashing_cursor(byte xpos, byte ypos, byte cursor_width, byte cursor_height, byte repeats) {
  for (byte r = 0; r <= repeats; r++) {    
    for (byte x = 0; x <= cursor_width; x++) {
      for (byte y = 0; y <= cursor_height; y++) {
        plot(x+xpos, y+ypos, 1);
      }
    }
    
    if (repeats > 0) {
      delay(400);
    } else {
      delay(70);
    }
        
    for (byte x = 0; x <= cursor_width; x++) {
      for (byte y = 0; y <= cursor_height; y++) {
        plot(x+xpos, y+ypos, 0);
      }
    }   
    //if cursor set to repeat, wait a while
    if (repeats > 0) {
     delay(400); 
    }
  }
}

void ht1632c::fade_down() {
  char intensity;
  for (intensity=14; intensity >= 0; intensity--) {
    sendcmd(0, HT1632_CMD_PWM + intensity); //send intensity commands using CS0 for display 0
    sendcmd(1, HT1632_CMD_PWM + intensity); //send intensity commands using CS0 for display 1
    delay(_fadedelay);
  }
  //clear the display and set it to full brightness again so we're ready to plot new stuff
  clear();
  sendcmd(0, HT1632_CMD_PWM + 15);
  sendcmd(1, HT1632_CMD_PWM + 15);
}

void ht1632c::fade_up() {
  char intensity;
  for ( intensity=0; intensity < 15; intensity++) {
    sendcmd(0, HT1632_CMD_PWM + intensity); //send intensity commands using CS0 for display 0
    sendcmd(1, HT1632_CMD_PWM + intensity); //send intensity commands using CS0 for display 1
    delay(_fadedelay);
  }
}

/******************************************************************************
 * private methods
 ******************************************************************************/

void ht1632c::chipselect (byte chipno) {
	digitalWriteFast2(HT1632_CS_PIN, 0);
}

void ht1632c::chipfree (byte chipno) {
	digitalWriteFast2(HT1632_CS_PIN, 1);
}

void ht1632c::writebits (byte bits, byte firstbit) {
	while (firstbit) {
		digitalWriteFast2(HT1632_WRCLK_PIN, LOW);
		if (bits & firstbit) {
		  digitalWriteFast2(HT1632_DATA_PIN, HIGH);
		} 
		else {
		  digitalWriteFast2(HT1632_DATA_PIN, LOW);
		}
		digitalWriteFast2(HT1632_WRCLK_PIN, HIGH);
		firstbit >>= 1;
	}
}

void ht1632c::sendcmd (byte d, byte command) {
	chipselect(HT1632_CS_PIN);        // Select chip
	writebits(HT1632_ID_CMD, 1<<2);  // send 3 bits of id: COMMMAND
	writebits(command, 1<<7);        // send the actual command
	writebits(0, 1);         	  // one extra dont-care bit in commands.
	chipfree(HT1632_CS_PIN);          //done
}

void ht1632c::senddata (byte d, byte address, byte data) {
	chipselect(HT1632_CS_PIN);      // Select chip
	writebits(HT1632_ID_WR, 1<<2); // Send ID: WRITE to RAM
	writebits(address, 1<<6);      // Send address
	writebits(data, 1<<3);         // Send 4 bits of data
	chipfree(HT1632_CS_PIN);        // Done.
}

void ht1632c::setup(byte data, byte wrclk, byte displays) {
	_displays = displays;
	
	for (byte d=0; d<_displays; d++) {
		pinMode(HT1632_CS_PIN, OUTPUT);

		digitalWriteFast2(HT1632_CS_PIN, HIGH);  // Unselect (active low)
		 
		pinMode(HT1632_WRCLK_PIN, OUTPUT);
		pinMode(HT1632_DATA_PIN, OUTPUT);

		sendcmd(d, HT1632_CMD_SYSON);    // System on 
		sendcmd(d, HT1632_CMD_LEDON);    // LEDs on 
		sendcmd(d, HT1632_CMD_COMS01);   // NMOS Output 24 row x 24 Com mode

		for (byte i=0; i<128; i++)
	  		senddata(d, i, 0);  // clear the display!
	}
	
	direct_write(true);
}

byte ht1632c::get_shadowram(byte x, byte y) {
  byte addr, bitval;

	// TODO: rewrite;
  //select display depending on plot values passed in
  byte d = x / _geometry_x;
  x = x - _geometry_x*d; 

  bitval = 8>>(y&3);  // compute which bit will need set
  addr = (x<<2) + (y>>2);       // compute which memory word this is in 
  return (0 != (_shadowram[(d * 96) + addr] & bitval));
}

void ht1632c::snapshot_shadowram() {
	for (byte i=0; i< sizeof _shadowram; i++) {
		_shadowram[i] = (_shadowram[i] & 0x0F) | _shadowram[i] << 4;  // Use the upper bits
	}
}

byte ht1632c::get_snapshotram(byte x, byte y) {
  byte addr, bitval;

  byte d = x / _geometry_x;
  x = x - _geometry_x*d;

  bitval = 128>>(y&3);  // user upper bits!
  addr = (x<<2) + (y>>2);   // compute which memory word this is in 
  if (_shadowram[(d * 96) + addr] & bitval)
    return 1;
  return 0;
}

void ht1632c::set_display_geometry(byte x, byte y) {
	_geometry_x = x;
	_geometry_y = y;
}

/* graphic primitives based on Bresenham's algorithms */

void ht1632c::line(int x0, int y0, int x1, int y1, byte color)
{
  int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = dx+dy, e2; /* error value e_xy */

  for(;;) {
    plot(x0, y0, color);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2*err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

void ht1632c::rect(int x0, int y0, int x1, int y1, byte color)
{
  line(x0, y0, x0, y1, color); /* left line   */
  line(x1, y0, x1, y1, color); /* right line  */
  line(x0, y0, x1, y0, color); /* top line    */
  line(x0, y1, x1, y1, color); /* bottom line */
}

void ht1632c::circle(int xm, int ym, int r, byte color)
{
  int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
  do {
    plot(xm - x, ym + y, color); /*   I. Quadrant */
    plot(xm - y, ym - x, color); /*  II. Quadrant */
    plot(xm + x, ym - y, color); /* III. Quadrant */
    plot(xm + y, ym + x, color); /*  IV. Quadrant */
    r = err;
    if (r >  x) err += ++x * 2 + 1; /* e_xy+e_x > 0 */
    if (r <= y) err += ++y * 2 + 1; /* e_xy+e_y < 0 */
  } while (x < 0);
}

void ht1632c::ellipse(int x0, int y0, int x1, int y1, byte color)
{
  int a = abs(x1 - x0), b = abs(y1 - y0), b1 = b & 1; /* values of diameter */
  long dx = 4 * (1 - a) * b * b, dy = 4 * (b1 + 1) * a * a; /* error increment */
  long err = dx + dy + b1 * a * a, e2; /* error of 1.step */

  if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
  if (y0 > y1) y0 = y1; /* .. exchange them */
  y0 += (b + 1) / 2; /* starting pixel */
  y1 = y0 - b1;
  a *= 8 * a; 
  b1 = 8 * b * b;

  do {
    plot(x1, y0, color); /*   I. Quadrant */
    plot(x0, y0, color); /*  II. Quadrant */
    plot(x0, y1, color); /* III. Quadrant */
    plot(x1, y1, color); /*  IV. Quadrant */
    e2 = 2 * err;
    if (e2 >= dx) { x0++; x1--; err += dx += b1; } /* x step */
    if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
  } while (x0 <= x1);

  while (y0 - y1 < b) {  /* too early stop of flat ellipses a=1 */
    plot(x0 - 1, ++y0, color); /* -> complete tip of ellipse */
    plot(x0 - 1, --y1, color); 
  }
}

void ht1632c::bezier(int x0, int y0, int x1, int y1, int x2, int y2, byte color)
{
  int sx = x0 < x2 ? 1 : -1, sy = y0<y2 ? 1 : -1; /* step direction */
  int cur = sx * sy * ((x0 - x1) * (y2 - y1) - (x2 - x1) * (y0 - y1)); /* curvature */
  int x = x0 - 2 * x1 + x2, y = y0 - 2 * y1 + y2, xy = 2 * x * y * sx * sy;
                                /* compute error increments of P0 */
  long dx = (1 - 2 * abs(x0 - x1)) * y * y + abs(y0 - y1) * xy - 2 * cur * abs(y0 - y2);
  long dy = (1 - 2 * abs(y0 - y1)) * x * x + abs(x0 - x1) * xy + 2 * cur * abs(x0 - x2);
                                /* compute error increments of P2 */
  long ex = (1 - 2 * abs(x2 - x1)) * y * y + abs(y2 - y1) * xy + 2 * cur * abs(y0 - y2);
  long ey = (1 - 2 * abs(y2 - y1)) * x * x + abs(x2 - x1) * xy - 2 * cur * abs(x0 - x2);

  if (cur == 0) { line(x0, y0, x2, y2, color); return; } /* straight line */
     
  x *= 2 * x; y *= 2 * y;
  if (cur < 0) {                             /* negated curvature */
    x = -x; dx = -dx; ex = -ex; xy = -xy;
    y = -y; dy = -dy; ey = -ey;
  }
  /* algorithm fails for almost straight line, check error values */
  if (dx >= -y || dy <= -x || ex <= -y || ey >= -x) {        
    line(x0, y0, x1, y1, color);                /* simple approximation */
    line(x1, y1, x2, y2, color);
    return;
  }
  dx -= xy; ex = dx+dy; dy -= xy;              /* error of 1.step */

  for(;;) {                                         /* plot curve */
    plot(x0, y0, color);
    ey = 2 * ex - dy;                /* save value for test of y step */
    if (2 * ex >= dx) {                                   /* x step */
      if (x0 == x2) break;
      x0 += sx; dy -= xy; ex += dx += y; 
    }
    if (ey <= 0) {                                      /* y step */
      if (y0 == y2) break;
      y0 += sy; dx -= xy; ex += dy += x; 
    }
  }
}

/* returns the pixel value (RED, GREEN, ORANGE or 0/BLACK) of x, y coordinates */

byte ht1632c::getpixel (byte x, byte y)
{
	return get_shadowram(x,y);
}

/* boundary flood fill with the seed in x, y coordinates */

void ht1632c::fill_r(byte x, byte y, byte color)
{
  if(!getpixel(x, y))
  {
    plot(x, y, color);
    fill_r(++x, y ,color);
    x = x - 1 ;
    fill_r(x, y-1, color);
    fill_r(x, y+1, color);
  }
}

void ht1632c::fill_l(byte x, byte y, byte color)
{
  if(!getpixel(x, y))
  {
    plot(x, y, color);
    fill_l(--x, y, color);
    x = x + 1 ;
    fill_l(x, y-1, color);
    fill_l(x, y+1, color);
  }
}

void ht1632c::fill(byte x, byte y, byte color)
{
  fill_r(x, y, color);
  fill_l(x-1, y, color);
}

void ht1632c::scrolltext(int y, const char *text, int delaytime, int times, byte dir)
{
  int c = 0, x, len = strlen(text) + 1;
  byte char_length = _font_width+1;
  byte char_height = _font_height;
  while (times) {
    for ((dir) ? x = - (len * char_length) : x = _geometry_x; (dir) ? x <= _geometry_x : x > - (len * char_length); (dir) ? x++ : x--)
    {
	  //direct_write(false);
	  for (int i = 0; i < len; i++)
      {
		int coord = x + char_length * i;
		int xx = coord + char_length-1;
		if (coord < -char_length || coord > _geometry_x) continue;		
        	put_char(coord,  y, text[i]);
		line(xx, y, xx, y+char_height, 0);
      }
	  //render();
	  //direct_write(true);
      c++;
      delay(delaytime);
    }
    times--;
  }
}

void ht1632c::direct_write(bool direct) {
	_direct_write = direct;
}

void ht1632c::render() {
  byte addr, bitval;

  for (byte x=0; x < _geometry_x; x++) {
	for (byte y=0; y < _geometry_y; y++) {
    	byte d = x / _geometry_x;
    	x = x - _geometry_x*d; 

  	    bitval = 8>>(y&3);  // compute which bit will need set
  	    addr = (x<<2) + (y>>2);       // compute which memory word this is in 
		senddata(d, addr, _shadowram[(d * 96) + addr]);
    }
  }
}

void ht1632c::brightness(char intensity) {
	if (intensity < 0 || intensity >= 15) return;	
    sendcmd(0, HT1632_CMD_PWM + intensity); //send intensity commands using CS0 for display 0
    sendcmd(1, HT1632_CMD_PWM + intensity); //send intensity commands using CS0 for display 1
}
