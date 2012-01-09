#include "ht1632c.h"
#include <digitalWriteFast.h>

// sure electronics 24x16 panel connected to pins
// DATA - pin 10
// WRCLK - pin 11
// CS1 - pin 4
ht1632c panel;

void setup() {

}

void loop() {
  demoFlashingCursor();
  demoScrollingText();
  demoLines();
  demoRects();
  demoCircles();
  demoFill();
}

void demoFlashingCursor() {
   panel.clear();
   panel.set_font(5,7);
   panel.flashing_cursor(0,1,5,6,3);
   byte x = 0;
   char* text = "DEMO";
   for (byte i=0; i<strlen(text); i++) {
      panel.flashing_cursor(i*6,1,5,6,1);
      delay(50);
      panel.put_char(i*6,1,text[i]);
      delay(400);
   }
   delay(2000);
   panel.fade_down();
}

void demoScrollingText() {
  panel.clear();
  panel.fade_up();
  panel.scrolltext(1, "WELCOME TO THE SURE ELECTRONICS DISPLAY DEMO", 12, 1, 0);
  delay(1000);
}

void demoLines() {
  for (byte i=0; i<20; i++) {
    byte x1 = random(0,23);
    byte y1 = random(0,15);
    byte x2 = random(0,23);
    byte y2 = random(0,15);
    panel.line(x1,y1,x2,y2,1);
    delay(50);
    //panel.fade_down();
    panel.clear();
  }
}

void demoRects() {
  
}

void demoCircles() {
  for (byte j=0; j<20; j++) {
  byte xm = random(0,23);
  byte ym = random(0,15);
  byte r = random(1,16);
   for (byte i = 0; i<r; i++) {
     panel.circle(xm,ym,i,1);
      delay(50);
     panel.circle(xm,ym,i,0); 
   }
   panel.circle(xm,ym,r,1);
   //delay(200);
   //panel.fade_down();
   panel.clear();
  }
}

void demoFill() {
}

