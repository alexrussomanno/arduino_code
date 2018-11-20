/*
Uses three (3) pressure transducers and one (1) pressure regulator.
 Applies a ramp up to max_pressure, increasing 1/255 analog output every time_step
 Records (2) pressures throughout as fast as possible.
 */

int gauge[]={10, 11, 12, 13, 14, 15}; // set pins according to appropriate pins on Arduino
int gauge_type[]={1, 1, 1, 1, 1, 2};
int gauges_on = 0;

//int valve[] = {0,31,33,35,37,39,41,43,45};
int valve[] = {0,38,40,42,44,46,48,50,52};
int regulator = 3;

int time_step = 50;
int max_pressure = 100;

// pressure gauges line fit
float m1 = 0.122396557;
float b1 = -12.32408416;

float m2 = 0.037207304;
float b2 = -3.773052632;

unsigned long prev_time;
unsigned long current_time;
long start_time;
int val;
  
void setup() {
  pinMode(regulator,OUTPUT);
  for (int i=0; i < 9; i++){
    pinMode(valve[i], OUTPUT);
  }
  Serial.begin(9600); 
  delay(1000);  // Run the following, enter slope and int values below in loop, then comment out this section

}

void loop() {
  Serial.println("Press enter to begin");
  while (Serial.read() != 10);
  prev_time = millis();
  current_time = millis();
  start_time = current_time;
  
  while (Serial.read() != 10){
    while (Serial.available() == 0){
      current_time = millis();
      Serial.print(millis()-start_time);   
      Serial.print(" ");
      
      for (int i=1; i < 9; i++){
        Serial.print(digitalRead(valve[i])); Serial.print(" ");
      } 
      Serial.print("   ");
      if (gauges_on==1){
        for (int i=0; i < sizeof(gauge); i++){
          if (gauge_type[i]==1) Serial.print((float)analogRead(gauge[i])*m1+b1); Serial.print(" ");
          if (gauge_type[i]==2) Serial.print((float)analogRead(gauge[i])*m2+b2); Serial.print(" ");
        }
      }
      Serial.println();
    }
    val = Serial.parseInt();
    Serial.read();
    if (digitalRead(valve[val])==HIGH){
      digitalWrite(valve[val],LOW);
    }
    else {
      digitalWrite(valve[val],HIGH);
    }
  }
}

//void pressure_calibration(){
//  Serial.println("Set pressure to 0 and press enter");
//  while (Serial.read() != 10);
//  v1_0 = (float)analogRead(transducer1)/1023*5.0;
//  v2_0 = (float)analogRead(transducer2)/1023*5.0;
//  v3_0 = (float)analogRead(transducer3)/1023*5.0;
//
//  Serial.println("Set pressure to 15 and press enter");
//  while (Serial.read() != 10);
//  v1_10 = (float)analogRead(transducer1)/1023*5.0;
//  v2_10 = (float)analogRead(transducer2)/1023*5.0;
//  v3_10 = (float)analogRead(transducer3)/1023*5.0;
//
//  slope1 = calibration_pressure/(v1_10-v1_0);
//  slope2 = calibration_pressure/(v2_10-v2_0);
//  slope3 = calibration_pressure/(v3_10-v3_0);
//
//  int1 = (float)-v1_0*slope1;
//  int2 = (float)-v2_0*slope2;
//  int3 = (float)-v3_0*slope3;
//  
//  Serial.print("slope1 ="); Serial.print(slope1,DEC); Serial.println(";");
//  Serial.print("slope2 ="); Serial.print(slope2,DEC); Serial.println(";");
//  Serial.print("slope3 ="); Serial.print(slope3,DEC); Serial.println(";");
//  Serial.print("int1 ="); Serial.print(int1,DEC); Serial.println(";");
//  Serial.print("int2 ="); Serial.print(int2,DEC); Serial.println(";");
//  Serial.print("int3 ="); Serial.print(int3,DEC); Serial.println(";");
//}

