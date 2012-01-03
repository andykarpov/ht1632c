/*
 * ht1632c.h
 * defintions for Holtek ht1632C LED driver.
 * Updated for the HT1632C by Nick H
 * Modified by Andrey Karpov
 */

#ifndef _HT1632C_H_
#define _HT1632C_H_

#define HT1632_DATA_PIN 10 /* Arduino digital pin connected to display DATA pin */
#define HT1632_WRCLK_PIN 11 /* Arduino digital pin connected to display WRCLK pin */
#define HT1632_CS_PIN 4 /* Arduino digital pin connected to display CS1 pin */
#define HT1632_GEOMETRY_X 24 /* display width */
#define HT1632_GEOMETRY_Y 16 /* display height */

/*
 * commands written to the chip consist of a 3 bit "ID", followed by
 * either 9 bits of "Command code" or 7 bits of address + 4 bits of data.
 */
#define HT1632_ID_CMD 4		/* ID = 100 - Commands */
#define HT1632_ID_RD  6		/* ID = 110 - Read RAM */
#define HT1632_ID_WR  5		/* ID = 101 - Write RAM */
#define HT1632_ID_BITS (1<<2)   /* IDs are 3 bits */

#define HT1632_CMD_SYSDIS 0x00	/* CMD= 0000-0000-x Turn off oscil */
#define HT1632_CMD_SYSON  0x01	/* CMD= 0000-0001-x Enable system oscil */
#define HT1632_CMD_LEDOFF 0x02	/* CMD= 0000-0010-x LED duty cycle gen off */
#define HT1632_CMD_LEDON  0x03	/* CMD= 0000-0011-x LEDs ON */
#define HT1632_CMD_BLOFF  0x08	/* CMD= 0000-1000-x Blink ON */
#define HT1632_CMD_BLON   0x09	/* CMD= 0000-1001-x Blink Off */
#define HT1632_CMD_SLVMD  0x10	/* CMD= 0001-00xx-x Slave Mode */
#define HT1632_CMD_MSTMD  0x14	/* CMD= 0001-01xx-x Master Mode */
#define HT1632_CMD_RCCLK  0x18	/* CMD= 0001-10xx-x Use on-chip clock */
#define HT1632_CMD_EXTCLK 0x1C	/* CMD= 0001-11xx-x Use external clock */
#define HT1632_CMD_COMS00 0x20	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS01 0x24	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS10 0x28	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_COMS11 0x2C	/* CMD= 0010-ABxx-x commons options */
#define HT1632_CMD_PWM    0xA0	/* CMD= 101x-PPPP-x PWM duty cycle */
#define HT1632_CMD_BITS (1<<7)

#include <Arduino.h>

#undef round

class ht1632c
{
  private:
  	byte _shadowram[384];  // our copy of the display's RAM
  	byte _displays;
  	byte _geometry_x;
  	byte _geometry_y;
	byte _font_width;
	byte _font_height;
  	static const byte _fadedelay = 40;
	bool _direct_write;
    void chipselect (byte);
	void chipfree (byte);
	void writebits (byte, byte);
	void sendcmd (byte, byte);
	void senddata (byte, byte, byte);
	void setup(byte, byte, byte);
	void set_display_geometry(byte, byte); 
  public:
    ht1632c();
	void plot (char, char, char);
	void line (char, char, char, char, char);
	void clear(void);
	void set_font(byte, byte);
	void put_char(byte, byte, char);
	void putstring(byte, byte, char*);
	void flashing_cursor(byte, byte, byte, byte, byte);
	void fade_down(void);
	void fade_up(void);
	void brightness(char);
	byte get_shadowram(byte, byte);
	void snapshot_shadowram();
	byte get_snapshotram(byte, byte);
	
	void direct_write(bool);
	void render();
	byte getpixel (byte x, byte y);
    void line(int x0, int y0, int x1, int y1, byte color);
    void rect(int x0, int y0, int x1, int y1, byte color);
    void circle(int xm, int ym, int r, byte color);
    void ellipse(int x0, int y0, int x1, int y1, byte color);
    void fill_r (byte x, byte y, byte color);
    void fill_l (byte x, byte y, byte color);
    void fill (byte x, byte y, byte color);
    void bezier(int x0, int y0, int x1, int y1, int x2, int y2, byte color);
	void scrolltext(int y, const char *text, int delaytime, int times, byte dir);
};

extern ht1632c ht1632;

#endif  // _HT1632C_H_

