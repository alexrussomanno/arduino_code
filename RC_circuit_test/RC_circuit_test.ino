/*
Uses two (2) pressure transducers and one (1) pressure regulator.
 Applies a ramp up to max_pressure, increasing 1/255 analog output every time_step
 Records (2) pressures throughout as fast as possible.
 */

int regulator = 3;
int light = 4;
int transducer1 = A8;
int transducer2 = A9;
int transducer3 = A10;

int valve[] = {
  0,44,24,26,28,30,32,34};
int time_step = 400;
int min_pressure = 0;
int max_pressure = 15;

float calibration_pressure =15;
float slope1; 
float int1;
float slope2; 
float int2;
float slope3; 
float int3;
float v1_0;  
float v2_0; 
float v3_0;
float v1_10; 
float v2_10; 
float v3_10;

int incomingByte = 0;
char junk;

void setup() {
  pinMode(regulator,OUTPUT);
  pinMode(light,OUTPUT);
  for (int i=1; i < 8; i++){
    pinMode(valve[i], OUTPUT);
  }
  Serial.begin(9600); 

  // Run the following, enter slope and int values below in loop, then comment out this section
  // pressure_calibration();
}

void loop() {
  slope1 = 7.4853658676;
  slope2 = 7.4400000572;
  int1 = -3.6674816608 ;
  int2 = -3.8414632797;




  while (Serial.read() != 10);
  digitalWrite(valve[1],HIGH);
  digitalWrite(light,HIGH);
  //  Serial.println(max_pressure*.9);
  //  while (Serial.read() != 10);
  long start_time = millis();

  unsigned long current_time = millis();
  long end_time = millis()+100000;
  long time_delay = 1000;
  float output_pressure = 0;
  int test_over=0;
  while (current_time < end_time){    
//  while (Serial.read() != 10){
    current_time = millis();
    output_pressure = (float)analogRead(transducer1)/1023*5.0*slope1+int1;
    Serial.print(current_time-start_time);  
    Serial.print(" ");
    Serial.println(output_pressure);
    if (output_pressure > max_pressure*.99 && test_over == 0){
      end_time = current_time + time_delay;
      test_over = 1;
    }
  }
  digitalWrite(valve[1],LOW);
  digitalWrite(light,LOW);


  //  int x = 1;
  //  unsigned long prev_time = millis();
  //  unsigned long current_time = millis();
  //  long start_time = current_time;
  //  int i = 30;
  //  
  ////  Electronic Pressure regulator
  //    while (i > min_pressure-1){
  //      current_time = millis();
  //      if (current_time > prev_time + time_step){
  //        analogWrite(regulator,i);
  //        if (i == max_pressure) x = -1;
  //        i = i + x;
  //        prev_time = current_time;
  //      }
  //      int output_volt1 = analogRead(transducer1);
  //      int output_volt2 = analogRead(transducer2);
  //      Serial.print(millis()-start_time);        Serial.print(" ");
  //      Serial.print((float)output_volt1/1023*5.0*slope1+int1); Serial.print(" ");
  //      Serial.println((float)output_volt2/1023*5.0*slope2+int2); 
  //    }
  //    analogWrite(regulator,0);
  //////  Electronic Pressure regulator
  ////    while (i > -1){
  ////      current_time = millis();
  ////      if (current_time > prev_time + time_step){
  ////        analogWrite(regulator,i);
  ////        if (i == max_pressure) x = -1;
  ////        i = i + x;
  ////        prev_time = current_time;
  ////      }
  //


}

void pressure_calibration(){
  Serial.println("Set pressure to 0 and press enter");
  while (Serial.read() != 10);
  v1_0 = (float)analogRead(transducer1)/1023*5.0;
  v2_0 = (float)analogRead(transducer2)/1023*5.0;
  v3_0 = (float)analogRead(transducer3)/1023*5.0;
  Serial.println("v1_0, v2_0, and v3_0 are...");
  Serial.print(v1_0,DEC); 
  Serial.print(" ");
  Serial.print(v2_0,DEC); 
  Serial.print(" ");
  Serial.println(v3_0,DEC); 

  Serial.println("Set pressure to 15 and press enter");
  while (Serial.read() != 10);
  v1_10 = (float)analogRead(transducer1)/1023*5.0;
  v2_10 = (float)analogRead(transducer2)/1023*5.0;
  v3_10 = (float)analogRead(transducer3)/1023*5.0;
  Serial.println("v1_10, v2_10, and v3_10 are...");
  Serial.print(v1_10,DEC); 
  Serial.print(" "); 
  Serial.print(v2_10,DEC); 
  Serial.print(" ");
  Serial.println(v3_10,DEC);

  slope1 = calibration_pressure/(v1_10-v1_0);
  slope2 = calibration_pressure/(v2_10-v2_0);
  slope3 = calibration_pressure/(v3_10-v3_0);
  Serial.println("Therefore, m1, m2, and m3 are...");
  Serial.print(slope1,DEC); 
  Serial.print(" "); 
  Serial.print(slope2,DEC); 
  Serial.print(" ");
  Serial.println(slope3,DEC);

  int1 = (float)-v1_0*slope1;
  int2 = (float)-v2_0*slope2;
  int3 = (float)-v3_0*slope3;
  Serial.println("Therefore, b1, b2, and b3 are...");
  Serial.print(int1,DEC); 
  Serial.print(" ");
  Serial.print(int2,DEC); 
  Serial.print(" ");
  Serial.println(int3,DEC);
}


