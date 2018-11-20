#include <PS2Keyboard.h>

const int DATA_PIN = 4; // black
const int CLK_PIN = 3; // white
//brown = ground
//red = 5 V
PS2Keyboard keyboard; 

// 2-dimensional array of row pin numbers:
const int row[8] = {
  22, 24, 26, 28, 46, 48, 50, 52 };    // matrix pins 1, 2, 3, 4, 21, 22, 23, 24
const int col[8] = {
  30, 32, 34, 36, 38, 40, 42, 44 };    // matrix pins 5, 6, 7, 8, 9, 10, 11, 12   

int SER_Pin[] = {43,41,39,37,35,33,31};  // pin31 is attached to the closest data pin to the PWR on the board
int SRCLK_Pin = 45; //pin 11 on the 75HC595 - clock pin
int RCLK_Pin = 47;  //pin 12 on the 75HC595 - latch pin (BOTTOM/OUTERMOST PIN on the board)

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

boolean valve[num_col][num_row];

void setup(){
  for (int i=0; i < num_row; i++){
    pinMode(SER_Pin[i], OUTPUT);
  }
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);

  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT); 
    pinMode(row[thisPin], OUTPUT);  
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off: 
    digitalWrite(col[thisPin],LOW);   
    digitalWrite(row[thisPin],HIGH);
  }

  keyboard.begin(DATA_PIN,CLK_PIN);
  
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
//  if (register_num==1) valve[index] = value;
//  if (register_num==2) valve2[index] = value;
}

void loop(){
  while(keyboard.available()!=1){
    refreshScreen();
  }
  char key = keyboard.read();

  c = key - 96;                        // Converts ASCII Char into number for letter_val
                     
  if (place < 3) {
    x = place * 3;
    y = 0;
  }
  else {
    x = (place - 3) * 3;
    y = 4;
  }
  letter(c, x, y);
  update_valves();
  place++;
  if (place >= 6) {
    place = 0;
  }
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


void letter(int letter_val,int pos_x,int pos_y){
//  Place letter at a position on the grid. (x,y) corresponds to
//  desired location of upper left dot of the letter.
  switch(letter_val){
    //case 0 is just a blank 2x3 space
    case 0:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
      
    case 1:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 11:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 21:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 2:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 12:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 22:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 3:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 13:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 24:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 4:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 14:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 25:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 5:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 15:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 26:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 6:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 16:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    
    case 7:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 17:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
      
    case 8:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 18:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
      
    case 9:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 19:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    
    case 10:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 20:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    
    case 23:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= HIGH;
      break;

  }
}
