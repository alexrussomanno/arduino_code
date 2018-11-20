/*
Uses two (3) pressure transducers and one (1) pressure regulator.
Applies a ramp up to max_pressure, increasing 1/255 analog output every time_step
Records (3) pressures throughout as fast as possible.

To be used with find_opening_and_closing_pressures_10_15.m

*/

int regulator = 8;
int input_transducer = A8;
int output_transducer = A9;
int p_gain = A10;

int time_step = 500;
int max_pressure = 100;
int start_pressure = 0;

int transducer1 = A8;
int transducer2 = A9;
int transducer3 = A10;
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

int output_volt1;
int output_volt2;
int output_volt3;
int prev_output;

void setup() {
  pinMode(regulator,OUTPUT);
  Serial.begin(9600); 
  delay(1000);
// Run the following, enter slope and int values below in loop, then comment out this section
//  pressure_calibration();
  
slope1 =7.4671535491;
slope2 =7.4309926033;
slope3 =24.5520000457;
int1 =-3.7226278781;
int2 =-3.7772395610;
int3 =-12.0000000000;
while (Serial.read() != 10);
}

void loop() {
  
  
  
  int x = 1;
  unsigned long prev_time = millis();
  unsigned long current_time = millis();
  long start_time = current_time;
  unsigned long hold_time = 10000;
  int i = start_pressure;
  prev_output = analogRead(output_transducer);
  
//  Electronic Pressure regulator
    while (i > start_pressure-1){
      output_volt1 = analogRead(input_transducer);
      output_volt2 = analogRead(output_transducer);
      output_volt3 = analogRead(p_gain);
      
      current_time = millis();
      if (current_time > prev_time + time_step){
        if(abs(prev_output-output_volt2) < 4){
          
          analogWrite(regulator,i);
          
          if (i == max_pressure) {
            x=-1;
//            time_step=time_step/2;
          }
          
          i = i + x;
          
        }
        
        
//        {
//          if (x!=0) {
//            hold_time = current_time + hold_time;
//            x = 0; 
//          }   
//          if (current_time > hold_time) x= -1;      
//        }
        prev_output=output_volt2;
        prev_time = current_time;
        
      }
//      output_volt1 = analogRead(input_transducer);
//      output_volt2 = analogRead(output_transducer);
      Serial.print(millis()-start_time);        Serial.print(" ");
  //      Serial.print((float)i/255*5);  Serial.print(" ");
      Serial.print((float)output_volt1/1023*5.0*slope1+int1); Serial.print(" ");
      Serial.print((float)output_volt2/1023*5.0*slope2+int2); Serial.print(" ");
      Serial.print((float)output_volt3/1023*5.0*slope3+int3); Serial.print(" ");
      Serial.println(abs(prev_output-output_volt2));
    }
    
    
    analogWrite(regulator,0);
}

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
