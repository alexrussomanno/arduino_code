int valve[] = {
  0,22,24,26,28,30,32,34,36,38};

int transducer1 = A8;
int transducer2 = A9;

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

void setup() {
  for (int i=0; i < 9; i++){
    pinMode(valve[i], OUTPUT);
    digitalWrite(valve[i],LOW);
  }
  Serial.begin(9600); 
  delay(1000);  // Run the following, enter slope and int values below in loop, then comment out this section
//  pressure_calibration();

  slope1 =7.6533665657;

slope2 =7.6724996566;

int1 =-3.8902742385;

int2 =-3.7500000000;


}

void loop() {

  while (Serial.read() != 10);
  unsigned long prev_time = millis();
  unsigned long current_time = millis();
  long start_time = current_time;
  int val =0;
  int output_volt1;
  int output_volt2;
  digitalWrite(valve[5],HIGH);
  while (Serial.read() != 10){
    current_time = millis();
    output_volt1 = analogRead(transducer1);
    output_volt2 = analogRead(transducer2);

    Serial.print(millis()-start_time);   
    Serial.print(" ");
    Serial.print(abs((float)output_volt1/1023*5.0*slope2+int2)); 
    Serial.print(" ");
    Serial.println(abs((float)output_volt2/1023*5.0*slope2+int2));  
  }
  digitalWrite(valve[5],LOW);
}

void pressure_calibration(){
  Serial.println("Set pressure to 0 and press enter");
  digitalWrite(valve[5],LOW);
  while (Serial.read() != 10);
  v1_0 = (float)analogRead(transducer1)/1023*5.0;
  v2_0 = (float)analogRead(transducer2)/1023*5.0;

  
  Serial.println("Set pressure to 15 and press enter");
  digitalWrite(valve[5],HIGH);
  while (Serial.read() != 10);
  v1_10 = (float)analogRead(transducer1)/1023*5.0;
  v2_10 = (float)analogRead(transducer2)/1023*5.0;


  slope1 = calibration_pressure/(v1_10-v1_0);
  slope2 = calibration_pressure/(v2_10-v2_0);


  int1 = (float)-v1_0*slope1;
  int2 = (float)-v2_0*slope2;


  Serial.print("slope1 ="); 
  Serial.print(slope1,DEC); 
  Serial.println(";");
  Serial.print("slope2 ="); 
  Serial.print(slope2,DEC); 
  Serial.println(";");

  Serial.print("int1 ="); 
  Serial.print(int1,DEC); 
  Serial.println(";");
  Serial.print("int2 ="); 
  Serial.print(int2,DEC); 
  Serial.println(";");

}


