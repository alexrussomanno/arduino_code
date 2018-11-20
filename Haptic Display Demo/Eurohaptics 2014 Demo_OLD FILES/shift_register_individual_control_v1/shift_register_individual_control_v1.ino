int SER_Pin = 1;   //pin 14 on the 75HC595
int SER_Pin2 = 2;   //pin 14 on the 75HC595
int RCLK_Pin = 8;  //pin 12 on the 75HC595
int SRCLK_Pin = 12; //pin 11 on the 75HC595

//How many of the shift registers - change this
#define number_of_74hc595s 1 

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];
boolean registers2[numOfRegisterPins];

void setup(){
  pinMode(SER_Pin, OUTPUT);
  pinMode(SER_Pin2, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);


  //reset all register pins
  clearRegisters();
  writeRegisters();
}               

//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
     registers2[i] = LOW;
  }
} 

//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){

  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];
    int val2 = registers2[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SER_Pin2,val2);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int register_num, int index, int value){
  if (register_num==1) registers[index] = value;
  if (register_num==2) registers2[index] = value;
}


void loop(){
  
  setRegisterPin(1,0, LOW);
  setRegisterPin(1,1, HIGH);
  setRegisterPin(1,2, LOW);
  setRegisterPin(1,3, HIGH);
  setRegisterPin(1,4, LOW);
  setRegisterPin(1,5, HIGH);
  setRegisterPin(1,6, LOW);
  setRegisterPin(1,7, HIGH);

  setRegisterPin(2,0, HIGH);
  setRegisterPin(2,1, HIGH);
  setRegisterPin(2,2, LOW);
  setRegisterPin(2,3, HIGH);
  setRegisterPin(2,4, LOW);
  setRegisterPin(2,5, HIGH);
  setRegisterPin(2,6, LOW);
  setRegisterPin(2,7, HIGH);  


  writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
  //Only call once after the values are set how you need.
}
