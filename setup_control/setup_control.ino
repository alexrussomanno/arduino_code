/*
Uses three (3) pressure transducers and one (1) pressure regulator.
 Applies a ramp up to max_pressure, increasing 1/255 analog output every time_step
 Records (2) pressures throughout as fast as possible.
 */

int regulator = 8;
int reg[]={0, 4, 5, 6, 7};

int transducer1 = A8;
int transducer2 = A9; 
int transducer3 = A10;
int transducer4 = A11;
int transducer5 = A12;
int transducer6 = A13;

int transducer[] = {
  0,A8,A9,A10,A11,A12,A13};
int analog_output[7];

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

int analog_output1;
int analog_output2;
int analog_output3;
int analog_output4;
int analog_output5;
int analog_output6;

int num_valves = 4;
int num_gages = 1;

int valve[] = {
  0,22,24,26,28,30,32,34,36,38};

int incomingByte = 0;
char junk;

void setup() {
  pinMode(regulator,OUTPUT);
  for (int i=0; i < 9; i++){
    pinMode(valve[i], OUTPUT);
  }
  Serial.begin(9600); 
  delay(1000);  // Run the following, enter slope and int values below in loop, then comment out this section
//  pressure_calibration();
  
  for (int i=1; i < 5; i++){
    pinMode(reg[i],OUTPUT);
  }
  
  slope1 =24.5520000457;
  //slope1=slope3;
  slope2=7.4671535491;

  int1 =-12.0000000000;
  //int1=int3;
  int2=-3.759124279;

}

void loop() {
  
  set_regulator(0);
  while (Serial.read() != 10);
  set_regulator(13);
  unsigned long prev_time = millis();
  unsigned long current_time = millis();
  long start_time = current_time;
  int val =0;

  while (Serial.read() != 10){
    while (Serial.available() == 0){
      current_time = millis();
      for (int i=1; i <= num_gages; i++){
        analog_output[i]=analogRead(transducer[i]);
      }
      //      analog_output1 = analogRead(transducer1);
      //      analog_output2 = analogRead(transducer2);
      //      analog_output3 = analogRead(transducer3);
      //      analog_output4 = analogRead(transducer4);
      //      analog_output5 = analogRead(transducer5);
      //      analog_output6 = analogRead(transducer6);

      Serial.print(current_time-start_time);   
      Serial.print(" ");

      for (int i=1; i <= num_valves; i++){
        Serial.print(digitalRead(valve[i])); 
        Serial.print(" ");
      }
      for (int i=1; i <= num_gages; i++){
        //        Serial.print(analogRead(transducer[i])); Serial.print(" ");
        Serial.print(analog_output[i]); Serial.print(" ");
//        Serial.print(abs((float)analog_output[i]/1023*5.0*slope2+int2)); 
        Serial.print(" ");
      }
      Serial.println();
      //      Serial.print(digitalRead(valve[8])); 
      //      Serial.print("   ");
      //      Serial.print(abs((float)analog_output1/1023*5.0*slope2+int2)); 
      //      Serial.print(" ");
      //      Serial.print(abs((float)analog_output2/1023*5.0*slope2+int2));  
      //      Serial.print(" ");
      //      Serial.print(abs((float)analog_output3/1023*5.0*slope1+int1));
      //      Serial.print(" ");
      //      Serial.print(abs((float)analog_output4/1023*5.0*slope1+int1));
      //      Serial.print(" ");
      //      Serial.print(abs((float)analog_output5/1023*5.0*slope1+int1));
      //      Serial.print(" ");
      //      Serial.println(abs((float)analog_output6/1023*5.0*slope1+int1));
      //      Serial.print("   ");
    }

    val = Serial.parseInt();
    Serial.read();
    if (digitalRead(valve[val])==HIGH) digitalWrite(valve[val],LOW);
    else                               digitalWrite(valve[val],HIGH);

  }
  

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

void pressure_calibration(){
  Serial.println("Set pressure to 0 and press enter");
  while (Serial.read() != 10);
  v1_0 = (float)analogRead(transducer1)/1023*5.0;
  v2_0 = (float)analogRead(transducer2)/1023*5.0;
  //  v3_0 = (float)analogRead(transducer3)/1023*5.0;

  Serial.println("Set pressure to 15 and press enter");
  while (Serial.read() != 10);
  v1_10 = (float)analogRead(transducer1)/1023*5.0;
  v2_10 = (float)analogRead(transducer2)/1023*5.0;
  //  v3_10 = (float)analogRead(transducer3)/1023*5.0;

  slope1 = calibration_pressure/(v1_10-v1_0);
  slope2 = calibration_pressure/(v2_10-v2_0);
  //  slope3 = calibration_pressure/(v3_10-v3_0);

  int1 = (float)-v1_0*slope1;
  int2 = (float)-v2_0*slope2;
  //  int3 = (float)-v3_0*slope3;

  Serial.print("slope1 ="); 
  Serial.print(slope1,DEC); 
  Serial.println(";");
  Serial.print("slope2 ="); 
  Serial.print(slope2,DEC); 
  Serial.println(";");
  //  Serial.print("slope3 ="); Serial.print(slope3,DEC); Serial.println(";");
  Serial.print("int1 ="); 
  Serial.print(int1,DEC); 
  Serial.println(";");
  Serial.print("int2 ="); 
  Serial.print(int2,DEC); 
  Serial.println(";");
  //  Serial.print("int3 ="); Serial.print(int3,DEC); Serial.println(";");
}


