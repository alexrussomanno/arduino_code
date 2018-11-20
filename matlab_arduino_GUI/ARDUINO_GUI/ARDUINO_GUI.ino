/*
Program that works with "arduino_matlab_sync.m"
Reads analog signal from 4 pins. When any serial data is received by the arduino, the program sends 
four 16 bit numbers across serial port representing 0-5V signals from the analog pins converted to 0-1023.

*/
//unsigned long time;
//int time_trunc;
int gauge[]={10, 11, 12, 13, 14, 15}; // set pins according to appropriate pins on Arduino

int valve_start=38;
int valve[9];

void setup(){
  for (int i=1; i < 9; i++){
    valve[i]=valve_start+2*(i-1);
  }
  for (int i=0; i < 9; i++){
    pinMode(valve[i], OUTPUT);
    digitalWrite(valve[i],LOW);
  }
  Serial.begin(57600);
//  Serial.println("ready");
}

void loop()
{
  byte valve_num = 0;
  unsigned int data;
  
  while(Serial.available()==0); // wait until serial data is received
  valve_num=Serial.read(); // empty the serial input buffer
  if (valve_num>0 && valve_num!=9) {
    if (digitalRead(valve[valve_num])==HIGH){
      digitalWrite(valve[valve_num],LOW);
    }
    else {
      digitalWrite(valve[valve_num],HIGH);
    }
  }
  else if (valve_num==9){
    for (int i=0; i < 9; i++){
      digitalWrite(valve[i],LOW);
    }
  }
  for (int i=0; i<6; i++){
    data =(unsigned int)analogRead(gauge[i]);
    byte buf[2]; // create an array of bytes
    buf[0] = data & 255; // assign least significant bits to buf[0] by applying AND with 11111111
    buf[1] = (data >> 8)  & 255; // assign most significant bits to buf[1] by shifting 8 bits to the right and applying AND with 11111111
    Serial.write(buf,sizeof(buf)); // send array of 2 bytes through serial port
  }
}


//  byte incomingByte = 0;
//  while(Serial.available()==0); // wait until serial data is received
//  incomingByte=Serial.read(); // empty the serial input buffer
//  Serial.write(incomingByte);
