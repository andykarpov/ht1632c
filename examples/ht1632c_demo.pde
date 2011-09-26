#include "ht1632c.h"

// sure electronics 24x16 panel connected to pins
// DATA - pin 10
// WRCLK - pin 11
// CS1 - pin 4
ht1632c panel(24,16, 10,11,4);

void setup() {

}

void loop() {
  demoScrollingText();
  demoLines();
  demoRects();
  demoCircles();
  demoFill();
}

void demoScrollingText() {
  panel.clear();
  panel.fade_up();
  panel.scrolltext(1, "SURE ELECTRONICS HT1632C DISPLAY DEMO", 0, 5, 0);
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
    panel.fade_down();
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
   delay(200);
   panel.fade_down();
   panel.clear();
  }
}

void demoFill() {
}

