/*Important pin information regarding interrupts for the Arduino Mega
http://arduino.cc/en/Main/ArduinoBoardMega*/


//#define ENCPINA 21            // Encoder Channel A - This pin can call an ISR on Arduino Mega
//#define ENCPINB 20            // Encoder Channel B - This pin can call an ISR on Arduino Mega

#define CH_A 19            // Encoder Channel A - This pin can call an ISR on Arduino Mega
#define CH_B 18            // Encoder Channel B - This pin can call an ISR on Arduino Mega
//boolean CH_A_initial;
//boolean CH_B_initial;
volatile int encPos=0;


void setup() {
  pinMode(CH_A, INPUT);
  pinMode(CH_B, INPUT);
  attachInterrupt(4, readEncoderA,CHANGE);
  attachInterrupt(5, readEncoderB, CHANGE);
  Serial.begin(9600); 
}

void loop(){
  Serial.println(encPos,DEC);
  
//  delay(1000);
//  Serial.println("Channel A");
//  Serial.println(CH_A_initial);
//  Serial.println("Channel B");
//  Serial.println(CH_B_initial);

  
}

void readEncoderA(){
  if(digitalRead(CH_A) ^ digitalRead(CH_B))
    encPos--;
  else
    encPos++;
}

void readEncoderB(){
  if(digitalRead(CH_A) ^ digitalRead(CH_B))
    encPos++;
  else
    encPos--;
}
