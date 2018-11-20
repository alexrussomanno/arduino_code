/*
Uses three (3) pressure transducers and one (1) pressure regulator.
 Applies a ramp up to max_pressure, increasing 1/255 analog output every time_step
 Records (2) pressures throughout as fast as possible.
 */

int regulator = 3;
int transducer1 = A10;
int transducer2 = A11;
int transducer3 = A12;
int transducer4 = A13;
int transducer5 = A8;
int transducer6 = A9; 

int time_step = 50;

int valve[] = {0,22,24,26,28,30,32,34,36,38};

int data = valve[1];
int clk1 = valve[2];
int clk2 = valve[3];
int source = valve[5];

int incomingByte = 0;
char junk;

void setup() {
  pinMode(regulator,OUTPUT);
  for (int i=0; i < 9; i++){
    pinMode(valve[i], OUTPUT);
  }
  Serial.begin(9600); 
  delay(1000);  // Run the following, enter slope and int values below in loop, then comment out this section
}

void loop() {

  while (Serial.read() != 10);
  unsigned long prev_time = millis();
  unsigned long current_time = millis();
  long start_time = current_time;
  int val =0;
  digitalWrite(source,HIGH);
  digitalWrite(clk1,HIGH);
  digitalWrite(clk2,HIGH);
  delay(1000);
//  val=1;
  while (Serial.read() != 10){
//  for (int i=0; i<20; i++){
    while(Serial.available()==0);
    val = Serial.parseInt();
    Serial.read();
   
   // Set the data input
    if (val==1){
      Serial.println("Shift in 1");
      digitalWrite(data,LOW);
//      val=0;
    }
    else{
      Serial.println("Shift in 0");
      digitalWrite(data,HIGH);
//      val=1;
    }
    delay(50);                          
    
    // Run a clock cycle
    digitalWrite(clk1,LOW);
    delay(125);
    digitalWrite(clk1,HIGH);
    delay(25);
    
    digitalWrite(clk2,LOW);
    delay(125);
    digitalWrite(clk2,HIGH);
    delay(25);
     
  }

}

