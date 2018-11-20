 #include <PS2Keyboard.h>
  
  #define DATA_PIN 2
  #define CLK_PIN 3
  PS2Keyboard keyboard;
  
  int SER_Pin[] = {22,24,26,28,30,32,34}; //{0,1,2,3,4,5,6};  //pin 14 on the 75HC595 - data pins
  int RCLK_Pin = 31;  //pin 12 on the 75HC595 - latch pin (BOTTOM PIN)
  int SRCLK_Pin = 33; //pin 11 on the 75HC595 - clock pin

//  int row[] = {22,24,26,28,30};
//  int col[] = {0,1,2,3,4};
//  int arrow[] = {10,11,12,13};
//  boolean arrow_state[]={LOW,LOW,LOW,LOW};
  
  /*
  arrow[0] - up
  arrow[1] - right
  arrow[2] - down
  arrow[3] - left
  */
  
  #define num_col 8
  #define num_row 7
  #define max_snake_length 20
  

  
  boolean valve[num_col][num_row];
//  boolean leds[num_col][num_row];
 
  byte key;
  byte val;
  char current_letter;
  void setup(){
//    Serial.begin(9600);
//    keyboard.begin(DATA_PIN,CLK_PIN);
    keyboard.begin(DATA_PIN,CLK_PIN);
    randomSeed(analogRead(0));
//    for (int i=0; i < num_col; i++){
//      pinMode(col[i], OUTPUT);
//    }
//    for (int i=0; i < num_row; i++){
//      pinMode(row[i], OUTPUT);
//    }
    for (int i=0; i < num_row; i++){
      pinMode(SER_Pin[i], OUTPUT);
    }
    pinMode(RCLK_Pin, OUTPUT);
    pinMode(SRCLK_Pin, OUTPUT);
    clear_all();
//    for (int i=0; i < 4; i++){
//      pinMode(arrow[i],INPUT);
//    }
  }      
void loop(){
  if(keyboard.available()) {
    key = keyboard.read();
    val = key - '0';
    clear_all();
  }
  if (val==49) current_letter='a';
  if (val==50) current_letter='b';
  if (val==51) current_letter='c';
  if (val==52) current_letter='d';
  
  type(current_letter,1);
  update_valves();
  delay(50);
    
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
    
 
 void clear_all(){
    for(int i = 0; i < num_col; i++){
       for (int j = 0; j < num_row; j++){
        valve[i][j] = LOW;
       }
    }
  }


void type(char letter, int pos){
  int start_col;
  int start_row;
  switch(pos){
    case 1:
      start_col=0;
      start_row=0;
      break;
    case 2:
      start_col=3;
      start_row=0;
      break;
    case 3:
      start_col=6;
      start_row=0;
      break;
    case 4:
      start_col=0;
      start_row=4;
      break;
    case 5:
      start_col=3;
      start_row=4;
      break;
    case 6:
      start_col=6;
      start_row=4;
      break;
  }
  switch(letter){
    case 'a':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'b':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'c':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'd':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'e':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'f':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'g':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'h':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'i':
      valve[start_col][start_row]  = LOW; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'j':
      valve[start_col][start_row]  = LOW; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'k': 
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'l':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'm':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'n':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'o':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'p':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'q':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'r':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 's':
      valve[start_col][start_row]  = LOW; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 't':
      valve[start_col][start_row]  = LOW; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= LOW;
      break;
    case 'u':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      break;
    case 'v':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      break;
    case 'w':
      valve[start_col][start_row]  = LOW; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= LOW; valve[start_col+1][start_row+1]= HIGH;
    case 'x':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= LOW;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      break;
    case 'y':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = HIGH;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      break;
    case 'z':
      valve[start_col][start_row]  = HIGH; valve[start_col+1][start_row]  = LOW;
      valve[start_col][start_row+1]= LOW; valve[start_col+1][start_row+1]= HIGH;
      valve[start_col][start_row+2]= HIGH; valve[start_col+1][start_row+1]= HIGH;
      break;
      
  }
}
