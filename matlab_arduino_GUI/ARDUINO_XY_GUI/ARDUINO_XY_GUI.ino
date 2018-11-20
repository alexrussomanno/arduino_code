/*
Program that works with "arduino_matlab_sync.m"
Reads analog signal from 4 pins. When any serial data is received by the arduino, the program sends 
four 16 bit numbers across serial port representing 0-5V signals from the analog pins converted to 0-1023.

*/
//unsigned long time;
//int time_trunc;
int gauge[]={10, 11, 12, 13, 14, 15}; // set pins according to appropriate pins on Arduino
//int valve[] = {0,22,24,26,28,30,32,34,36};
//int valve[] = {0,31,33,35,37,39,41,43,45};

#define num_col 8
#define num_row 7

// Initialize pins for shift register array for valve control
int SER_Pin[] = {43,41,39,37,35,33,31};  // pin31 is attached to the closest data pin to the GND on the board
int SRCLK_Pin = 45; // pin 11 on the 75HC595 - clock pin
int RCLK_Pin = 47;  // pin 12 on the 75HC595 - latch pin (BOTTOM/OUTERMOST PIN on the board)

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

void setup(){
  for (int i=0; i < num_row; i++){
    pinMode(SER_Pin[i], OUTPUT);
  }
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  
//  for (int i=0; i < 9; i++){
//    pinMode(valve[i], OUTPUT);
//    digitalWrite(valve[i],LOW);
//  }
  clear_all();
  update_valves();
  Serial.begin(57600);
//  Serial.println("ready");
}

void loop()
{
  byte valve_num = 0;
  unsigned int data;
  int count;
  
  while(Serial.available()==0); // wait until serial data is received
  valve_num=Serial.read(); // empty the serial input buffer

  if (valve_num>0 && valve_num!=100) {
    count=1;
    for(int j=0; j<num_row; j++){
        for(int i = 0; i < num_col; i++){
            if (valve_num==count){
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
  }
  else if (valve_num==100){
    clear_all();
  }
  update_valves();
  
  for (int i=0; i<6; i++){
    data =(unsigned int)analogRead(gauge[i]);
    byte buf[2]; // create an array of bytes
    buf[0] = data & 255; // assign least significant bits to buf[0] by applying AND with 11111111
    buf[1] = (data >> 8)  & 255; // assign most significant bits to buf[1] by shifting 8 bits to the right and applying AND with 11111111
    Serial.write(buf,sizeof(buf)); // send array of 2 bytes through serial port
  }
}

void clear_all(){
//set all boolean valve states to LOW
  for(int i = 0; i < num_col; i++){
     for (int j = 0; j < num_row; j++){
      valve[i][j] = LOW;
     }
  }
} 

void update_valves(){
// updates the value of the solenoid valves to correspond to the boolean "valve"
  digitalWrite(RCLK_Pin, LOW);

  for(int i = num_col - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);
    for (int j = 0; j < num_row; j++){
      digitalWrite(SER_Pin[j], valve[i][j]);
    }     
    digitalWrite(SRCLK_Pin, HIGH);
    
  }
  digitalWrite(RCLK_Pin, HIGH);

}

//  byte incomingByte = 0;
//  while(Serial.available()==0); // wait until serial data is received
//  incomingByte=Serial.read(); // empty the serial input buffer
//  Serial.write(incomingByte);
