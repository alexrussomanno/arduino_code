int gauge[]={10, 11, 12, 13, 14, 15}; // set pins according to appropriate pins on Arduino
//int valve[] = {0,22,24,26,28,30,32,34,36};
int valve[] = {0,31,33,35,37,39,41,43,45};
int source = valve[1];
int input = valve [2];
int gate = valve[3];
int trig = valve[4];
int output = gauge[2];

float m = 0.122396557;
float b = -12.32408416;

float output_pressure;

void setup(){
  for (int i=0; i < 9; i++){
    pinMode(valve[i], OUTPUT);
    digitalWrite(valve[i],LOW);
  }
  Serial.begin(57600);
  delay(500);
  while(Serial.read()!=10);
  Serial.println("begin");
  digitalWrite(source,HIGH);
  digitalWrite(gate,HIGH);
  digitalWrite(trig,HIGH);
  
  
  
//  Serial.println("ready");
}

void loop(){
  unsigned long counter = 0;
  
  // start the output at LO by setting input to HI and cycling once
  digitalWrite(input,HIGH);
  int desired_output_state=1;  
  
  while(Serial.read()!=10);
  
  while (true) {
    delay(100);
    gate_cycle();
    trig_cycle();
    delay(3000);
    output_pressure=(float)analogRead(output)*m+b;
    Serial.print("Count: "); Serial.print(counter); Serial.print(" ");
    Serial.print("Desired Output State: "); Serial.print(desired_output_state); Serial.print(" ");
    Serial.print("Output Pressure: "); Serial.println(output_pressure);
    counter++;
    if (desired_output_state==0 && output_pressure<10){            
      
      desired_output_state=1;
      digitalWrite(input,HIGH);
    }
    else if (desired_output_state==1 && output_pressure>10){
      
      desired_output_state=0;
      digitalWrite(input,LOW);
    }
    else if (Serial.read()==10){
      break;
    }
    else{
      Serial.println("FAILURE");
      break;
    } 
  }
}

void gate_cycle(){
  digitalWrite(gate,LOW);
  delay(200);
  digitalWrite(gate,HIGH);
  delay(50);
}

void trig_cycle(){
  digitalWrite(trig,LOW);
  delay(200);
  digitalWrite(trig,HIGH);
  delay(50);
}
