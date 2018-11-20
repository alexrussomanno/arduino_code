#include <TimerOne.h>

int SER_Pin[] = {43,41,39,37,35,33,31};  // pin31 is attached to the closest data pin to the PWR on the board
int SRCLK_Pin = 45; //pin 11 on the 75HC595 - clock pin
int RCLK_Pin = 47;  //pin 12 on the 75HC595 - latch pin (BOTTOM/OUTERMOST PIN on the board)

// 2-dimensional array of row pin numbers:
const int row[8] = {
  22, 24, 26, 28, 46, 48, 50, 52 };    // matrix pins 1, 2, 3, 4, 21, 22, 23, 24
const int col[8] = {
  30, 32, 34, 36, 38, 40, 42, 44 };    // matrix pins 5, 6, 7, 8, 9, 10, 11, 12   

#define num_col 8
#define num_row 7

int xpos = 3;         // the x and y position of the ball, default at (3,3)
int ypos = 3;
int _angle = 270;     // the direction of the ball, default straight down

int leftpad = 3;      // the x position of the left side of the paddle
                      // default at column 3 on row 6
int potpin = A7;      // rotary potentiometer on analog pin 7
int buttonpin = 5;    // push button on digital pin 5

byte brick[2][8];
boolean valve[num_col][num_row];

byte youwin[7][8] = { \
    {1, 1, 0, 1, 0, 0, 1, 0},  \
    {0, 1, 0, 0, 1, 0, 0, 0}, \
    {1, 1, 0, 1, 0, 0, 1, 1}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 1, 0, 1, 1}, \
    {1, 1, 0, 1, 0, 0, 0, 1}, \
    {0, 1, 0, 0, 0, 0, 1, 0} \
};

void setup(){
  for (int i=0; i < num_row; i++){
    pinMode(SER_Pin[i], OUTPUT);
  }
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(buttonpin, INPUT_PULLUP);

  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin],LOW);   
    digitalWrite(row[thisPin],HIGH);
  }
  
  Timer1.initialize(1000);
  Timer1.attachInterrupt(refreshScreen);
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      brick[j][i] = 1;      // sets all bricks to be on
    }
  }
  
  //reset all register pins
  clear_all();
  update_valves();
}               

//set all register pins to LOW
void clear_all(){
  for(int i = 0; i < num_col; i++){
     for (int j = 0; j < num_row; j++){
      valve[i][j] = LOW;
     }
  }
} 

//Set and display valve
//Only call AFTER all values are set how you would like (slow otherwise)
void update_valves(){
  digitalWrite(RCLK_Pin, LOW);
  for(int i = num_col - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);
    for (int j = 0; j < num_row; j++){
      int val = valve[i][j];
      digitalWrite(SER_Pin[j], val);
    }     
    digitalWrite(SRCLK_Pin, HIGH);
  }
  digitalWrite(RCLK_Pin, HIGH);
}

//set an individual pin HIGH or LOW
void set(int i, int j, boolean value){
  valve[i][j] = value;
}

void loop(){
  if (digitalRead(buttonpin) == 0)
    reset();
  calcPad();
  checkCollision();
  checkbricks();
  calcAngleIncrement();
  clear_all();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      valve[i][j] = brick[j][i];      
    }
  }
  
  valve[xpos][ypos] = HIGH;
  valve[leftpad][6] = HIGH;
  valve[leftpad + 1][6] = HIGH;
  valve[leftpad + 2][6] = HIGH;
  update_valves();
  delay(1000); 
}

void calcPad()	{
  leftpad = analogRead(potpin);
  leftpad = constrain(map(leftpad, 223, 800, 0, 5), 0, 5);	// numbers may need to change depending on pot
}

void checkCollision()
{
  if (ypos == 5)	// if ball is above pad
  {
    if (_angle == 225 || _angle == 270 || _angle == 315)	// if ball is going down
    {
      if (_angle == 225)
      {
        if (xpos == leftpad)
          _angle = 135;
        else if (xpos == leftpad + 1)
          _angle = 135;
        else if (xpos == leftpad + 2)
          _angle = 90;
        else if (xpos == leftpad + 3)
          _angle = 45;
      }
      else if (_angle == 270)
      {
        if (xpos == leftpad)
          _angle = 135;
        else if (xpos == leftpad + 1)
          _angle = 90;
        else if (xpos == leftpad + 2)
          _angle = 45;
      }
      else if (_angle == 315)
      {
        if (xpos == leftpad)
          _angle = 90;
        else if (xpos == leftpad + 1)
          _angle = 45;
        else if (xpos == leftpad + 2)
          _angle = 45;
        else if (xpos == leftpad - 1)
          _angle = 135;
      }
    }
  }
  
  if (xpos == 7)	// if ball is on right wall
  {
    if (_angle == 45) {
      if (brick[ypos - 1][xpos] == 1){  // if there is a brick above ball 
        brick[ypos - 1][xpos] = 0;   // breaks brick
        _angle = 225;
      }
      else if (brick[ypos - 1][xpos - 1] == 1){  // if there is a brick up-left of ball 
        brick[ypos - 1][xpos - 1] = 0;
        _angle = 225;
      }
      else {              // just bounces off wall
        if (ypos == 0) {
          _angle = 225;
        }
        else {
          _angle = 135;
        }
      }
    }
    else if (_angle == 315) {
      _angle = 225;
    }
  }
  else if (xpos == 0)	// if ball is on left wall
  {
    if (_angle == 135) {
      if (brick[ypos - 1][xpos] == 1){  // if there is a brick above ball 
        brick[ypos - 1][xpos] = 0;   // breaks brick
        _angle = 315;
      }
      else if (brick[ypos - 1][xpos + 1] == 1){  // if there is a brick up-right of ball 
        brick[ypos - 1][xpos + 1] = 0;
        _angle = 315;
      }
      else {              // just bounces off wall
        if (ypos == 0) {
          _angle = 315;
        }
        else {
          _angle = 45;
        }
      }
    }
    else if (_angle == 225) {
      _angle = 315;
    }
  }
  else if (ypos == 6)	// if ball is on bottom row
  {
    gameover();
    reset();	// ends game
  }

  else if (ypos == 0)	// if ball is on top row
  {
    if (_angle == 45) {
      if (brick[ypos + 1][xpos + 1] != 1) {   // if there is no brick down-right of ball
        _angle = 315;
      }
      else {
        brick[ypos + 1][xpos + 1] = 0;
        _angle = 225;
      }
    }
    else if (_angle == 135) {
      if (brick[ypos + 1][xpos - 1] != 1) {   // if there is no brick down-left of ball
        _angle = 225;
      }
      else {
        brick[ypos + 1][xpos - 1] = 0;
        _angle = 315;
      }
    }
    else if (_angle == 90) {
      _angle = 270;
    }
  }
  else if ((ypos == 1 || ypos == 2) && _angle < 225 && brick[ypos - 1][xpos] == 1)    // if ball is going up 
  {                                                                                   // and has a brick above it
    brick[ypos - 1][xpos] = 0;    // breaks brick
    if (_angle == 45)
      _angle = 315;
    else if (_angle == 135)
      _angle = 225;
    else if (_angle == 90)
      _angle = 270;
  }
  else if ((ypos == 1 || ypos == 2) && _angle == 135 && brick[ypos - 1][xpos] == 0 && brick[ypos - 1][xpos - 1] == 1)    // if ball is going up-left
  {                                                                                                                      // and does not have a brick above it
    brick[ypos - 1][xpos - 1] = 0;    // breaks brick
    _angle = 315;
  }
  else if ((ypos == 1 || ypos == 2) && _angle == 45 && brick[ypos - 1][xpos] == 0 && brick[ypos - 1][xpos + 1] == 1)    // if ball is going up-right
  {                                                                                                                      // and does not have a brick above it
    brick[ypos - 1][xpos + 1] = 0;    // breaks brick
    _angle = 225;
  }
}

void calcAngleIncrement()
{
  if (_angle == 90) {
    ypos -= 1;
  }
  else if (_angle == 45) {
    xpos += 1;
    ypos -= 1;
  }
  else if (_angle == 135) {
    xpos -= 1;
    ypos -= 1;
  }
  else if (_angle == 270) {
    ypos += 1;
  }
  else if (_angle == 225) {
    xpos -= 1;
    ypos += 1;
  }
  else if (_angle == 315) {
    xpos += 1;
    ypos += 1;
  }
}

void gameover()
{
  clear_all();
  update_valves();
  delay(750);
  
  valve[0][0]=HIGH;
  valve[1][1]=HIGH;
  valve[2][2]=HIGH;
  valve[3][3]=HIGH;
  valve[4][4]=HIGH;
  valve[5][5]=HIGH;
  valve[6][6]=HIGH;
  
  valve[6][0]=HIGH;
  valve[5][1]=HIGH;
  valve[4][2]=HIGH;
  valve[3][3]=HIGH;
  valve[2][4]=HIGH;
  valve[1][5]=HIGH;
  valve[0][6]=HIGH;
  update_valves();
  delay(1000); 
  clear_all();
}

void reset()
{ 
  xpos = int(random(3, 6));
  ypos = int(random(2, 4));
  _angle = 270;
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      brick[i][j] = HIGH;      // sets all bricks to be on
    }
  }
  delay(1000);
}

void checkbricks(){       // checks bricks to see if game is won
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      if (brick[j][i] == 1)
        return;
    }
  }
  wingame();
}

void wingame()
{
  for(int i = 0; i < num_col; i++){
    for (int j = 0; j < num_row; j++){
      valve[i][j] = youwin[j][i];
    }
  }
  update_valves();
  delay(5000);
  clear_all();
  reset();
}

void refreshScreen() {
  for (int thisPin = 0; thisPin < 8; thisPin++) { 
    // makes sure the LEDS are off 
    digitalWrite(col[thisPin], LOW);   
    digitalWrite(row[thisPin], HIGH);
  }

  for (int x = 0; x < num_col; x++) {
    for (int y = 0; y < num_row; y++) {
      if (valve[x][y] == HIGH) {
        digitalWrite(col[x], HIGH);
        digitalWrite(row[y], LOW);
        digitalWrite(col[x], LOW);
        digitalWrite(row[y], HIGH);
      }
    }
  }
}

