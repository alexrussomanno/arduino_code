/*
Uses two (2) pressure transducers and one (1) pressure regulator.
Applies a ramp up to max_pressure, increasing 1/255 analog output every time_step
Records (2) pressures throughout as fast as possible.
*/

int regulator = 3;
int input_transducer = A8;
int output_transducer = A9;

int time_step = 10;
int max_pressure = 255;

void setup() {
  pinMode(regulator,OUTPUT);
  Serial.begin(9600); 
  
}

void loop() {
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
      int output_volt1 = analogRead(input_transducer);
      int output_volt2 = analogRead(output_transducer);
//      Serial.print(millis()-start_time);        Serial.print(" ");
//  //      Serial.print((float)i/255*5);  Serial.print(" ");
//      Serial.print((float)output_volt1/1023*5.0); Serial.print(" ");
//      Serial.println((float)output_volt2/1023*5.0); 
    }
    
////    Manual pressure regulator
//  while (Serial.read() != 10){
//    current_time = millis();
//    int output_volt1 = analogRead(input_transducer);
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
//      int output_volt1 = analogRead(input_transducer);
//      int output_volt2 = analogRead(output_transducer);
//      Serial.print(millis());        Serial.print(" ");
////      Serial.print((float)i/255*5);  Serial.print(" ");
//      Serial.print((float)output_volt1/1023*5.0); Serial.print(" ");
//      Serial.println((float)output_volt2/1023*5.0); 
   } 


//  for(int i=0;i<=150;i++){
//    analogWrite(2,i);
//    delay(time_step);
//    int output_volt = analogRead(input_transducer);
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

