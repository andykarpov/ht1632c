#include <Wire.h>
#include "ht1632c.h"
#include <RealTimeClockDS1307.h>
#include "Button.h"

// sure electronics 24x16 panel connected to pins
// DATA - pin 10
// WRCLK - pin 11
// CS1 - pin 4
ht1632c panel(24,16,10,11,4);

Button btnMode(2, PULLUP);
Button btnSet(3, PULLUP);
Button btnPlus(5, PULLUP);

int seconds; // current seconds
int minutes; // current minutes
int hours; // current hours

long curTime = 0; // current time (timestamp)
long lastPush = 0; // last pushed settings button (timestamp)
int lastSec = 0; // last second value
boolean dotsOn = false; // current dots on / off flag

void setup() {

}

void loop() {
  // start clock if stopped
  if (RTC.isStopped()) {
    RTC.start();
  }

  // read clock values into buffers
  RTC.readClock();
  
  // update seconds / minutes / hours variables
  seconds = RTC.getSeconds();
  minutes = RTC.getMinutes();
  hours = RTC.getHours(); 
 
  curTime = millis();
  printTime(hours, minutes); // print time
  processDots(); // blink dots
  processTimeAdjustment(); // check if set time buttons pressed and adjust time
  delay(200);
}

/**
 * Print current time
 * @param int h
 * @param int m
 * @return void
 */
void printTime(int h, int m) {

    panel.putbigdigit(-1, 2, (h>9) ? (h/10) : 0);
    panel.putbigdigit( 5, 2, h % 10);

    panel.putbigdigit(12, 2, (m>9) ? (m/10) : 0);
    panel.putbigdigit(18, 2, m % 10);
}

void printDots(boolean on) 
{
/*  panel.plot(11, 4, on);
  panel.plot(11, 5, on);
  panel.plot(12, 4, on);
  panel.plot(12, 5, on);  
  
  panel.plot(11, 11, on);
  panel.plot(11, 10, on);
  panel.plot(12, 11, on);
  panel.plot(12, 10, on); */
  
  for (byte i=0; i<24; i++) {
    panel.plot(i,0, on);
    panel.plot(i,15, !on);
    delay(30);
  }
}

void processDots() {
    if (lastSec != seconds) {
      dotsOn = !dotsOn; 
      lastSec = seconds;
    }
    printDots(dotsOn);
}

void processTimeAdjustment() {
  // hours buttons pressed
  if (btnMode.isPressed()) {
    hours++;
    if (hours > 23) hours = 0;
    RTC.setHours(hours);
    RTC.setClock();
    lastPush = curTime;
  }
  // minutes button pressed
  if (btnSet.isPressed()) {
    minutes++;
    if (minutes > 59) minutes = 0;
    RTC.setMinutes(minutes);
    RTC.setClock();
    lastPush = curTime;
  }
}

