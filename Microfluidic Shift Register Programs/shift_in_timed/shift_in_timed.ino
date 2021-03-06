/*
For microfluidic shift register - Using the serial monitor, a user either enters 0 or 1.
The corresponding bubble state is applied to the shift register.
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
//int data = valve[1];
//int clk1 = valve[2];
//int clk2 = valve[3];
int data = valve[1];
int clk1 = valve[2];
int clk2 = valve[3];
int source = valve[4];
int val =0;

int incomingByte = 0;
char junk;

int reg[]={0, 4, 5, 6, 7};

void setup() {
  pinMode(regulator,OUTPUT);
  for (int i=0; i < 9; i++){
    pinMode(valve[i], OUTPUT);
    digitalWrite(valve[i],LOW);
  }
  for (int i=1; i < 5; i++){
    pinMode(reg[i],OUTPUT);
  }
  Serial.begin(9600); 
  Serial.println("Ready");
  delay(1000);  // Run the following, enter slope and int values below in loop, then comment out this section
}

void loop() {

  while (Serial.read() != 10);
  unsigned long prev_time = millis();
  unsigned long current_time = millis();
  long start_time = current_time;
  
  digitalWrite(source,HIGH);
//  set_regulator(13);
  digitalWrite(clk1,HIGH);
  digitalWrite(clk2,HIGH);
  delay(500);
  
//  val=1;
  while (true){
//  for (int i=0; i<3; i++){
    while(Serial.available()==0);
    val = Serial.parseInt();
    Serial.read();
    
    if (val==1){
      Serial.println("Shift in 1");
      digitalWrite(data,LOW);
      val=0;
    }
    else if (val==0){
      Serial.println("Shift in 0");
      digitalWrite(data,HIGH);
      val=1;
    }
    else break;
    
    delay(500);
    
    digitalWrite(clk1,LOW);
    delay(500);
    digitalWrite(clk1,HIGH);
//    delay(25);
    
    
    
    delay(500);
    
    digitalWrite(clk2,LOW);
    delay(500);
    digitalWrite(clk2,HIGH);
//    delay(25);
     
  }
//  set_regulator(0);

}

void set_regulator(int i){ 
     int a=i%2;      // calculate LSB   
     int b=i/2 %2;     
     int c=i/4 %2;        
     int d=i/8 %2;  //claculate MSB
     digitalWrite(reg[4],d);   //write MSB
     digitalWrite(reg[3],c);   
     digitalWrite(reg[2],b);    
     digitalWrite(reg[1],a);
}
//}

