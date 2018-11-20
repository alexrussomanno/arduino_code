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


// Initialize pins for shift register array for valve control
int SER_Pin[] = {43,41,37,39,35,33,31};  // pin31 is attached to the closest data pin to the GND on the board
int SRCLK_Pin = 45; // pin 11 on the 75HC595 - clock pin
int RCLK_Pin = 47;  // pin 12 on the 75HC595 - latch pin (BOTTOM/OUTERMOST PIN on the board)
String current_letter;

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

int gage[]={10, 11, 12, 13, 14, 15};
int gage_type[]={1, 1, 1, 1, 1, 2};
int valve_source[] = {22,24,26,28,30,32,34,36,38};

float m1 = 0.122396557;
float b1 = -12.32408416;

float m2 = 0.037207304;
float b2 = -3.773052632;

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
  
  
  //reset all shift register pins
  clear_all();
  update_valves();
  Serial.begin(57600);
  while(Serial.read()!=10);
  Serial.println("Begin...");
}               

// prints all of the valve states to the serial port in a matrix (1-56)
void print_matrix_state(){
  for (int k=0; k< num_row; k++){
    for (int l=0; l<num_col; l++){
      // 
      Serial.print(valve[l][k],BIN); Serial.print(" ");
//      if (l==num_col-1 && k==0) {
//        for (int i=0; i < sizeof(gage); i++){
//          if (gage_type[i]==1) Serial.print((float)analogRead(gage[i])*m1+b1); Serial.print(" ");
//          if (gage_type[i]==2) Serial.print((float)analogRead(gage[i])*m2+b2); Serial.print(" ");
//        }
//      }
    }
    Serial.println(); 
  }
  Serial.println(); 
}
  


void loop(){
  for (int i=1; i<27; i++){
    while(Serial.read()!=10);
    clear_all();
    Serial.read();    
    letter(i,0,0);
    letter(i-1,2,0);
    Serial.println(current_letter);
    update_valves();
  }

//  toggle_matrix();
  
}

// Reads in from serial monitor to toggle valve state
// Based on valve numbering 1-56 - top left, read like a book
void toggle_matrix(){
  int val;
  int count;
  if(Serial.available() != 0){
  
    val = Serial.parseInt();
    Serial.read();
    // toggle value of valves
    if (val==57) clear_all();
    count=1;
    
    for(int j=0; j<num_row; j++){
      for(int i = 0; i < num_col; i++){
          if (val==count){
            if (valve[i][j]==HIGH) {
              valve[i][j]=LOW;
            }
            else {
              valve[i][j]=HIGH;
            }
          }
          count++;  
      }
    }
    update_valves();
    val=0;
    print_matrix_state();
  }
}

