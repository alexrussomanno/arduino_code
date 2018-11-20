/*
Uses two (2) pressure transducers and one (1) pressure regulator.
Applies a ramp up to max_pressure, increasing 1/255 analog output every time_step
Records (2) pressures throughout as fast as possible.
*/

int regulator = 3;
int transducer1 = A8;
int transducer2 = A9;

int time_step = 100;
int max_pressure = 100;

float calibration_pressure =10;
float slope1; float int1;
float slope2; float int2;
float v1_0;  float v2_0;
float v1_10; float v2_10;

int incomingByte = 0;
char junk;

void setup() {
  pinMode(regulator,OUTPUT);
  Serial.begin(9600); 
  
  // Run the following, enter slope and int values below in loop, then comment out this section
  /*
  Serial.println("Set pressure to 0 and press enter");
  while (Serial.read() != 10);
  v1_0 = (float)analogRead(transducer1)/1023*5.0;
  v2_0 = (float)analogRead(transducer2)/1023*5.0;
  Serial.println("v1_0 and v2_0 are...");
  Serial.print(v1_0,DEC); Serial.print(" ");
  Serial.println(v2_0,DEC);
  
  Serial.println("Set pressure to 10 and press enter");
  while (Serial.read() != 10);
  v1_10 = (float)analogRead(transducer1)/1023*5.0;
  v2_10 = (float)analogRead(transducer2)/1023*5.0;
  Serial.println("v1_10 and v2_10 are...");
  Serial.print(v1_10,DEC); Serial.print(" "); Serial.print(" ");
  Serial.println(v2_10,DEC);
  
  slope1 = calibration_pressure/(v1_10-v1_0);
  slope2 = calibration_pressure/(v2_10-v2_0);
  Serial.println("Therefore, m1 and m2 are...");
  Serial.print(slope1,DEC); Serial.print(" "); Serial.print(" ");
  Serial.println(slope2,DEC);
  
  int1 = (float)-v1_0*slope1;
  int2 = (float)-v2_0*slope2;
  Serial.println("Therefore, b1 and b2 are...");
  Serial.print(int1,DEC); Serial.print(" ");
  Serial.println(int2,DEC);
  */
}

void loop() {
  slope1 = 7.386281490;
  slope2 = 7.3862814903;
  int1 = -3.610108375 ;
  int2 = -3.6823103427;
  
  while (Serial.read() != 10);
  int x = 1;
  unsigned long prev_time = millis();
  unsigned long current_time = millis();
  long start_time = current_time;
  int i = 1;
  
//  Electronic Pressure regulator
    while (i > -1){
      current_time = millis();
      if (current_time > prev_time + time_step){
        analogWrite(regulator,i);
        if (i == max_pressure) x = -1;
        i = i + x;
        prev_time = current_time;
      }
      int output_volt1 = analogRead(transducer1);
      int output_volt2 = analogRead(transducer2);
      Serial.print(millis()-start_time);        Serial.print(" ");
      Serial.print((float)output_volt1/1023*5.0*slope1+int1); Serial.print(" ");
      Serial.println((float)output_volt2/1023*5.0*slope2+int2); 
    }
  
////  Electronic Pressure regulator
//    while (i > -1){
//      current_time = millis();
//      if (current_time > prev_time + time_step){
//        analogWrite(regulator,i);
//        if (i == max_pressure) x = -1;
//        i = i + x;
//        prev_time = current_time;
//      }


      
    }
    
////    Manual pressure regulator
//  while (Serial.read() != 10){
//    current_time = millis();
//    int output_volt1 = analogRead(transducer1);
//    int output_volt2 = analogRead(output_transducer);
//    Serial.print(millis()-start_time);        Serial.print(" ");
//    Serial.print((float)output_volt1/1023*5.0); Serial.print(" ");
//    Serial.println((float)output_volt2/1023*5.0); 
//  }

//   int x = 1;
//   for (int i = 0; i > -1; i = i + x){
//      analogWrite(regulator,i);
//      if (i == max_pressure) x = -1;             // switch direction at peak
//      delay(time_step);
//      int output_volt1 = analogRead(transducer1);
//      int output_volt2 = analogRead(output_transducer);
//      Serial.print(millis());        Serial.print(" ");
////      Serial.print((float)i/255*5);  Serial.print(" ");
//      Serial.print((float)output_volt1/1023*5.0); Serial.print(" ");
//      Serial.println((float)output_volt2/1023*5.0); 
//   } 


//  for(int i=0;i<=150;i++){
//    analogWrite(2,i);
//    delay(time_step);
//    int output_volt = analogRead(transducer1);
//    Serial.print(millis());
//    Serial.print(" ");
//    Serial.print((float)i/255*5);
//    Serial.print(" ");
//    Serial.println((float)output_volt/1023*5.0);    
//  }
//  for(int i=99;i>=0;i--){
//    analogWrite(2,i);
//    delay(time_step);
//    int output_volt = analogRead(transducer1);
//    Serial.print(millis());
//    Serial.print(" ");
//    Serial.print((float)i/255*5);
//    Serial.print(" ");
//    Serial.println((float)output_volt/1023*5.0);
//  }
  
//  analogWrite(2,100);
//  Serial.println(analogRead(input));

