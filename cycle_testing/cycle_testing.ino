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
int max_pressure = 100;

float calibration_pressure = 15;
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

int valve[] = {0,22,24,26,28,30,32,34,36,38};

int incomingByte = 0;
char junk;

void setup() {
  pinMode(regulator,OUTPUT);
  for (int i=0; i < 9; i++){
    pinMode(valve[i], OUTPUT);
  }
  Serial.begin(9600); 
  delay(1000);  // Run the following, enter slope and int values below in loop, then comment out this section
//    pressure_calibration();
//slope1 =7.4671535491;
//
//slope2 =7.4309926033;

slope1 =24.5520000457;
//slope1=slope3;
slope2=7.4309926033;

//int1 =-3.7226278781;
//
//int2 =-3.7772395610;

int1 =-12.0000000000;
//int1=int3;
int2=-3.7772395610;

}

void loop() {

  while (Serial.read() != 10);
  unsigned long prev_time = millis();
  unsigned long current_time = millis();
  long start_time = current_time;
  int val =0;
  while (Serial.read() != 10){
    while (Serial.available() == 0){
      current_time = millis();
      int output_volt1 = analogRead(transducer1);
      int output_volt2 = analogRead(transducer2);
      int output_volt3 = analogRead(transducer3);
      int output_volt4 = analogRead(transducer4);
      int output_volt5 = analogRead(transducer5);
      int output_volt6 = analogRead(transducer6);
      //      Serial.print(millis()-start_time);        Serial.print(" ");
      //  //      Serial.print((float)i/255*5);  Serial.print(" ");
      Serial.print(millis()-start_time);   
      Serial.print(" ");
      
      for (int i=1; i < 9; i++){
        Serial.print(digitalRead(valve[i])); Serial.print(" ");
      }
//      Serial.print(digitalRead(valve[8])); 
      Serial.print("   ");
      Serial.print(abs((float)output_volt1/1023*5.0*slope1+int1)); 
      Serial.print(" ");
      Serial.print(abs((float)output_volt2/1023*5.0*slope1+int1));  
      Serial.print(" ");
      Serial.print(abs((float)output_volt3/1023*5.0*slope1+int1));
      Serial.print(" ");
      Serial.print(abs((float)output_volt4/1023*5.0*slope1+int1));
      Serial.print(" ");
      Serial.print(abs((float)output_volt5/1023*5.0*slope2+int2));
      Serial.print(" ");
      Serial.println(abs((float)output_volt6/1023*5.0*slope2+int2));
//      Serial.print("   ");
    }
    val = Serial.parseInt();
    Serial.read();
    if (digitalRead(valve[val])==HIGH){
      digitalWrite(valve[val],LOW);
    }
//    else if (val == 0) 
    else {
      digitalWrite(valve[val],HIGH);
    }
//    val = Serial.parseInt();
  }

  //  int x = 1;
  //  for (int i = 0; i > -1; i = i + x){
  //      analogWrite(regulator,i);
  //      if (i == max_pressure) x = -1;             // switch direction at peak
  //      delay(time_step);
  //      int output_volt1 = analogRead(transducer1);
  //      int output_volt2 = analogRead(transducer2);
  //      Serial.print(millis());        Serial.print(" ");
  ////      Serial.print((float)i/255*5);  Serial.print(" ");
  //      Serial.print((float)output_volt1/1023*5.0*slope1+int1); Serial.print(" ");
  //      Serial.println((float)output_volt2/1023*5.0*slope2+int2); 
  //   } 



  //  while (Serial.read() != 10);
  //  int x = 1;
  //  unsigned long prev_time = millis();
  //  unsigned long current_time = millis();
  //  long start_time = current_time;
  //  int i = 1;

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
//    int output_volt2 = analogRead(transducer2);
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
//      int output_volt2 = analogRead(transducer2);
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
void pressure_calibration(){
  Serial.println("Set pressure to 0 and press enter");
  while (Serial.read() != 10);
  v1_0 = (float)analogRead(transducer1)/1023*5.0;
  v2_0 = (float)analogRead(transducer2)/1023*5.0;
  v3_0 = (float)analogRead(transducer3)/1023*5.0;

  Serial.println("Set pressure to 15 and press enter");
  while (Serial.read() != 10);
  v1_10 = (float)analogRead(transducer1)/1023*5.0;
  v2_10 = (float)analogRead(transducer2)/1023*5.0;
  v3_10 = (float)analogRead(transducer3)/1023*5.0;

  slope1 = calibration_pressure/(v1_10-v1_0);
  slope2 = calibration_pressure/(v2_10-v2_0);
  slope3 = calibration_pressure/(v3_10-v3_0);

  int1 = (float)-v1_0*slope1;
  int2 = (float)-v2_0*slope2;
  int3 = (float)-v3_0*slope3;
  
  Serial.print("slope1 ="); Serial.print(slope1,DEC); Serial.println(";");
  Serial.print("slope2 ="); Serial.print(slope2,DEC); Serial.println(";");
  Serial.print("slope3 ="); Serial.print(slope3,DEC); Serial.println(";");
  Serial.print("int1 ="); Serial.print(int1,DEC); Serial.println(";");
  Serial.print("int2 ="); Serial.print(int2,DEC); Serial.println(";");
  Serial.print("int3 ="); Serial.print(int3,DEC); Serial.println(";");
}

