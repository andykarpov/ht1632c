/**
 * Arduino Pong on green 24x16 Sure Electronics display based on ht1632c chip
 * By Andrey Karpov
 * 
 * Creative Commons Non-Commerical/Attribution/Share-Alike license
 * creativecommons.org/licenses/by-nc-sa/2.0/
 */

#include <ht1632c.h>
#include <digitalWriteFast.h>
#include "pitches.h"

#define WHEEL_ONE_PIN A0 // analog pad 1
#define WHEEL_TWO_PIN A1 // analog pad 2
#define BUTTON_ONE_PIN 2 // digital button pin
#define SPEAKER_PIN 6 // speaker digital pin

#define PADDLE_HEIGHT 6
#define PADDLE_WIDTH 2

#define RIGHT_PADDLE_X 22
#define LEFT_PADDLE_X 0

#define IN_GAME 0 //in game state
#define IN_MENU 1 //in menu state
#define GAME_OVER 2 //game over state

#define LEFT_SCORE_X 3
#define RIGHT_SCORE_X 14
#define SCORE_Y 2

#define MAX_Y_VELOCITY 3
#define PLAY_TO 9

#define LEFT 0
#define RIGHT 1

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

ht1632c panel;

unsigned char x,y;
boolean buttonStatus = false;
int wheelOnePosition = 0;
int wheelTwoPosition = 0;
int rightPaddleY = 0;
int leftPaddleY = 0;
unsigned char ballX = 0;
unsigned char ballY = 0;
unsigned char prevBallX = 0;
unsigned char prevBallY = 0;
char ballVolX = 1;
char ballVolY = 1;
char prevBallVolX = 1;
char prevBallVolY = 1;

int leftPlayerScore = 0;
int rightPlayerScore = 0;

int frame = 0;
int state = IN_MENU;

void processInputs() {
  wheelOnePosition = analogRead(WHEEL_ONE_PIN);
  wheelTwoPosition = analogRead(WHEEL_TWO_PIN);
  buttonStatus = (digitalRead(BUTTON_ONE_PIN) == LOW);
}

void drawGameScreen() {
  //panel.clear();
  //draw right paddle
  rightPaddleY = ((wheelOnePosition / 8) * (16-PADDLE_HEIGHT))/ 128;
  x = RIGHT_PADDLE_X;
  for(int i=0; i<PADDLE_WIDTH; i++) {
    panel.line(x+i,0,x+i,rightPaddleY-1, 0);
    panel.line(x+i,rightPaddleY,x+i,rightPaddleY+PADDLE_HEIGHT,1);
    panel.line(x+i,rightPaddleY+PADDLE_HEIGHT+1, x+i, 15, 0);
  }

  //draw left paddle
  leftPaddleY = ((wheelTwoPosition / 8) * (16-PADDLE_HEIGHT))/ 128;
  x = LEFT_PADDLE_X;
  for(int i=0; i<PADDLE_WIDTH; i++) {
    panel.line(x+i,0,x+i,leftPaddleY-1, 0);
    panel.line(x+i,leftPaddleY,x+i,leftPaddleY+PADDLE_HEIGHT,1);
    panel.line(x+i,leftPaddleY+PADDLE_HEIGHT+1, x+i, 15, 0);
  }

  // clear prev ball position
  panel.plot(prevBallX, prevBallY, 0);

  //draw ball
  panel.plot(ballX, ballY, 1);
}

//player == LEFT or RIGHT
void playerScored(byte player) {
  if(player == LEFT) leftPlayerScore++;
  if(player == RIGHT) rightPlayerScore++;

  //draw score
  panel.clear();
  panel.set_font(5,12);
  char sc[2];
  sprintf(sc, "%d%d", leftPlayerScore, rightPlayerScore);
  panel.put_char(LEFT_SCORE_X,SCORE_Y, sc[0]);
  panel.put_char(RIGHT_SCORE_X,SCORE_Y, sc[1]);

  panel.rect(11,3,12,4,1);
  panel.rect(11,11,12,12,1);

  tone(SPEAKER_PIN, NOTE_E5, 200);
  
  delay(2000);
  
  panel.clear();

  //check for win
  if(leftPlayerScore == PLAY_TO || rightPlayerScore == PLAY_TO) {
    state = GAME_OVER; 
  }
  
  // correct angles
  ballVolX = (ballVolX > 0) ? -1 : 1;
  ballVolY = 0;
  
  // center ball
  ballX = (ballVolX > 0) ? 2 : 21;
  ballY = 8;
}

void drawMenu() {
  x = 0;
  y = 0;
  char volX = 1;
  char volY = 1;
  char prevVolX = 1;
  char prevVolY = 1;
  panel.clear();
  panel.set_font(5,7);
  panel.putstring(0,0,"PONG");
  delay(1000);
  while(!buttonStatus) {
    processInputs();
    if(x + volX < 0 || x + volX > 23) volX = -volX;
    if(y + volY < 0 || y + volY > 15) volY = -volY;
    if(panel.getpixel(x + volX, y + volY)) {
      //panel.plot(x + volX, y + volY, 0);
      
      if(panel.getpixel(x + volX, y - volY) == 0) {
        volY = -volY;
      }
      else if(panel.getpixel(x - volX, y + volY) == 0) {
        volX = -volX;
      }
      else {
        volX = -volX;
        volY = -volY; 
      }
    }
    
    if (prevVolX != volX || prevVolY != volY) {
      //tone(SPEAKER_PIN, NOTE_E1, 20);
    }
    
    prevVolX = volX;
    prevVolY = volY;
    
    panel.plot(x, y, 0);
    x += volX;
    y += volY;
    panel.plot(x, y, 1);
    delay(40);
  }
  panel.clear();
  ballX = 3;
  ballY = 8;
  ballVolX = 1;
  ballVolY = 0;
  state = IN_GAME;
}

void setup()  {
  pinMode(BUTTON_ONE_PIN, INPUT);
  digitalWrite(BUTTON_ONE_PIN, HIGH);
  pinMode(SPEAKER_PIN, OUTPUT);
  Serial.begin(9600);
  x=0;
  y=0;

  panel.clear();
  panel.brightness(14);

  ballX = 12;
  ballY = 8;
}

void loop() {
  processInputs();

  if(state == IN_MENU) {
    drawMenu(); 
  }
  if(state == IN_GAME) {
    
      prevBallX = ballX;
      prevBallY = ballY;
    
      ballX += ballVolX;
      ballY += ballVolY;

      // mirror from top and bottom
      if(ballY <= 0 || ballY >= 15) ballVolY = -ballVolY;
      
      // collision with left paddle
      if(ballVolX < 0 && ballX == LEFT_PADDLE_X+PADDLE_WIDTH-1 && ballY >= leftPaddleY && ballY <= leftPaddleY + PADDLE_HEIGHT) {
        ballVolX = -ballVolX; 
        ballVolY += 2 * ((ballY - leftPaddleY) - (PADDLE_HEIGHT / 2)) / (PADDLE_HEIGHT / 2);
      }
      
      // collision with right paddle
      if(ballVolX > 0 && ballX == RIGHT_PADDLE_X && ballY >= rightPaddleY && ballY <= rightPaddleY + PADDLE_HEIGHT) { 
        ballVolX = -ballVolX; 
        ballVolY += 2 * ((ballY - rightPaddleY) - (PADDLE_HEIGHT / 2)) / (PADDLE_HEIGHT / 2);
      }

      //limit vertical speed
      if(ballVolY > MAX_Y_VELOCITY) ballVolY = MAX_Y_VELOCITY;
      if(ballVolY < -MAX_Y_VELOCITY) ballVolY = -MAX_Y_VELOCITY;

      if (prevBallVolX != ballVolX || prevBallVolY != ballVolY) {
        tone(SPEAKER_PIN, NOTE_E1, 20);
      }
      
      prevBallVolX = ballVolX;
      prevBallVolY = ballVolY;

      if(ballX <= 0) {
        playerScored(RIGHT);
      }
      if(ballX >= 24) {
        playerScored(LEFT);
      }
    //if(buttonStatus) state = IN_MENU;

    drawGameScreen();
    delay(50);
  } 
  if(state == GAME_OVER) {
    panel.clear();
    panel.set_font(5,7);
    panel.putstring(0,0,"GAME");
    panel.putstring(0,8,"OVER"); 

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(SPEAKER_PIN, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER_PIN);
  }

    while(!buttonStatus) {
      processInputs();
      delay(100); 
    }
    //reset the scores
    leftPlayerScore = 0;
    rightPlayerScore = 0;
    state = IN_MENU;
  }
}
