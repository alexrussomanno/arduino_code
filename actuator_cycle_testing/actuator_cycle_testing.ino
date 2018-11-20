int gauge[]={10, 11, 12, 13, 14, 15}; // set pins according to appropriate pins on Arduino
//int valve[] = {0,22,24,26,28,30,32,34,36};

int valve_start=38;
int valve[9];

//int source = valve[1];
//int input = valve [2];
//int gate = valve[3];
//int trig = valve[4];
//int output = gauge[2];

float m1 = 0.122396557;
float b1 = -12.32408416;

float m2 = 0.037207304;
float b2 = -3.773052632;

float output_pressure;

void setup(){
  for (int i=1; i < 9; i++){
    valve[i]=valve_start+2*(i-1);
    pinMode(valve[i], OUTPUT);
    digitalWrite(valve[i],LOW);
  }
  Serial.begin(9600);
  delay(500);
  while(Serial.read()!=10);
  Serial.println("begin");
  
}

void loop(){
  unsigned long counter = 0;
  
  while(Serial.read()!=10);
  int num_valves=6;
  while (true) {
    counter++;
    
    Serial.print("Cycle: "); Serial.print(counter); 
    for (int i=1; i<num_valves+1;i++){
      digitalWrite(valve[i],HIGH);
    }
//    digitalWrite(valve[2],HIGH);
    delay(500);
    Serial.print(" Pressure: "); Serial.println((float)analogRead(gauge[4])*m1+b1);
    for (int i =1; i<num_valves+1;i++){
      digitalWrite(valve[i],LOW);
    }
//    digitalWrite(valve[2],LOW);  
    delay(500);

    if (Serial.read()==10) break;
  }
}

//void gate_cycle(){
//  digitalWrite(gate,LOW);
//  delay(200);
//  digitalWrite(gate,HIGH);
//  delay(50);
//}
//
//void trig_cycle(){
//  digitalWrite(trig,LOW);
//  delay(200);
//  digitalWrite(trig,HIGH);
//  delay(50);
//}
