#include <PS2Keyboard.h>

// http://en.wikipedia.org/wiki/PS/2_port

#define DATA_PIN 2 // black
#define CLK_PIN 3 // white
PS2Keyboard keyboard;
boolean arrow_state = LOW;
int dir = 4;

void setup() {
  keyboard.begin(DATA_PIN,CLK_PIN);

  Serial.begin(9600);
  Serial.println("hi");
  delay(1000);
  
}

void loop() {
//  check_direction();
  if(keyboard.available()) {
    byte dat = keyboard.read();
    byte val = dat - '0';
    Serial.println(val,DEC);
////    delay(500);
//    if(val >= 0 && val <= 9) {
//      Serial.print(val, DEC);
//    } else if(dat == PS2_ENTER) {
//      Serial.println();
//    } else if(dat == PS2_ESC) {
//      Serial.println("[ESC]");
//    } 
  }
}

//  int check_direction(){
//    if(keyboard.available()){
//      byte key = keyboard.read();
//      if(key==11) dir=0;
//      if(key==21) dir=1;
//      if(key==10) dir=2;
//      if(key==8) dir=3;
//    }
////    else arrow_state=LOW; 
//  }
