  /*
  ORDER OF PINS ON PCB
  *from top down perspective*
    |-----------------|
    | ooooooooo   ooo | 
    |                 |
    |                 | 
    |                 | 
    |                 | 
    |                 | 
    |_________________|
  
    *left to right*
    RCLK_Pin
    SRCLK_Pin
    Row1
    Row2
    Row3
    Row4
    Row5
    Row6
    Row7
    ...
    GND
    5V
    24V
  */
  
/*
// Initialize the keyboard input if using a keyboard
#include <PS2Keyboard.h>
const int DATA_PIN = 4; // black cable
const int CLK_PIN = 3; // white cable
// brown = ground
// red = 5 V
PS2Keyboard keyboard; 
*/

/*
// LED MATRX: 2D dimensional array of row pin numbers for LED screen:
const int row[8] = {
  22, 24, 26, 28, 46, 48, 50, 52 };    // matrix pins 1, 2, 3, 4, 21, 22, 23, 24
const int col[8] = {
  30, 32, 34, 36, 38, 40, 42, 44 };    // matrix pins 5, 6, 7, 8, 9, 10, 11, 12   
*/

//  // *****Initialize pins for valve array*****
//  // For Arduino MEGA
//  int SER_Pin[] = {43,41,39,37,35,33,31};  // pin31 is attached to the closest data pin to the PWR on the board
//  int SRCLK_Pin = 45; //pin 11 on the 75HC595 - clock pin
//  int RCLK_Pin = 47;  //pin 12 on the 75HC595 - latch pin (BOTTOM/OUTERMOST PIN on the board)
  
  // For Arduino UNO
  int SER_Pin[] = {11,10,9,8,7,6,5};  // pin5 is attached to the closest data pin to the PWR on the board
  int SRCLK_Pin = 12; //pin 11 on the 75HC595 - clock pin
  int RCLK_Pin = 13;  //pin 12 on the 75HC595 - latch pin (BOTTOM/OUTERMOST PIN on the board)


//  int a = 1; int b = 2; int c = 3; int d = 4; int e = 5; int f = 6; 
//  int g = 7;  int h = 8;  int i = 9;  int j = 10; int k = 11; int l = 12; 
//  int m = 13; int n = 14; int o = 15; int p = 16; int q = 17; int r = 18; 
//  int s = 19; int t = 20; int u = 21; int v = 22; int w = 23; int x = 24; 
//  int y = 25; int z = 26;

#define num_col 8
#define num_row 7

int place = 0;
int c;
int x; 
int y;

// Define a matrix to hold boolean values for each valve
boolean valve[num_col][num_row];
/*
          cols
    0 1 2 3 4 5 6 7
  0 o o o o o o o o
r 1 o o o o o o o o
o 2 o o o o o o o o
w 3 o o o o o o o o
s 4 o o o o o o o o
  5 o o o o o o o o
  6 o o o o o o o o

*/

 //// ************************************************ ////

#include "haptic_demo_functions.h"

void setup(){
  for (int i=0; i < num_row; i++){
    pinMode(SER_Pin[i], OUTPUT);
  }
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);

// LED ARRAY Initialization
/*
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins for the LED display:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin],LOW);   
    digitalWrite(row[thisPin],HIGH);
  }
*/

// Keyboard initialization
//  keyboard.begin(DATA_PIN,CLK_PIN);
  
  //reset all shift register pins
  clear_all();
  update_valves();
  Serial.begin(9600);
}               

void loop(){

//  while(keyboard.available()!=1){}
//  char key = keyboard.read();

  for(int j=0; j<num_row; j++){
    for(int i = 0; i < num_col; i++){
    
      valve[i][j] = HIGH;
      update_valves();
      delay(1000);
      clear_all();      
    }
    
    
    update_valves();
  }
}
