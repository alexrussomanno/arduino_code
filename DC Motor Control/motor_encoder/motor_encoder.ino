#define CH_A 19            // Encoder Channel A - This pin can call an ISR on Arduino Mega
#define CH_B 18            // Encoder Channel B - This pin can call an ISR on Arduino Mega

volatile int encPos=0;

int M1 = 3;           // the pin that the Motor1 is attached to
int D1 = 2;
int Cmd = 0;       
int key = 0;

// the setup routine runs once when you press reset:
void setup()  { 
  pinMode(CH_A, INPUT); //Encoder channel A
  pinMode(CH_B, INPUT); //Encoder channel B
  attachInterrupt(4, readEncoderA, CHANGE); // attach interrupt to encoder channel A
  attachInterrupt(5, readEncoderB, CHANGE); // attach interrupt to encoder channel B
  
  pinMode(M1, OUTPUT);
  pinMode(D1, OUTPUT);
  
  Serial.begin(9600);
  // declare pin 9 to be an output:
  
  while(Serial.read() != 10);
  encPos = 0;
  
} 

// the loop routine runs over and over again forever:
void loop()  { 
  
  if(encPos < 6000){
    move_motor(100);
    Serial.print(millis()); 
    Serial.print(" ");
    Serial.println(encPos);
  }
  move_motor(0);
  
}


void move_motor(int velocity){
  Cmd = abs(velocity);
  
  if (velocity < 0) digitalWrite(D1,HIGH);
  else if (velocity > 0) digitalWrite(D1,LOW);
  
  analogWrite(M1,Cmd);
 
}
/* 
ENCODER STUFF
*/
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

