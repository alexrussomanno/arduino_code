/*
For Arduino UNO
Program that works with "arduino_matlab_sync.m"
Reads analog signal from 4 pins. When any serial data is received by the arduino, the program sends 
four 16 bit numbers across serial port representing 0-5V signals from the analog pins converted to 0-1023.

*/
//unsigned long time;
//int time_trunc;
int gauge[]={0, 1, 2, 3, 4, 5}; // set pins according to appropriate pins on Arduino
int valve[] = {0,2,3,4,5,8,9,10,11};
void setup()
{
  // put your setup code here, to run once:
  for (int i=0; i < 9; i++){
    pinMode(valve[i], OUTPUT);
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
  if (valve_num!=0) {
    if (digitalRead(valve[valve_num])==HIGH){
      digitalWrite(valve[valve_num],LOW);
    }
    else {
      digitalWrite(valve[valve_num],HIGH);
    }
  }
  
  for(int j=0; j<6; j++){
    for (int i=0; i<5;i++){
      data =(unsigned int)analogRead(gauge[i]);
      byte buf[2]; // create an array of bytes
      buf[0] = data & 255; // assign least significant bits to buf[0] by applying AND with 11111111
      buf[1] = (data >> 8)  & 255; // assign most significant bits to buf[1] by shifting 8 bits to the right and applying AND with 11111111
      Serial.write(buf,sizeof(buf)); // send array of 2 bytes through serial port
    }
  }
}


//  byte incomingByte = 0;
//  while(Serial.available()==0); // wait until serial data is received
//  incomingByte=Serial.read(); // empty the serial input buffer
//  Serial.write(incomingByte);
