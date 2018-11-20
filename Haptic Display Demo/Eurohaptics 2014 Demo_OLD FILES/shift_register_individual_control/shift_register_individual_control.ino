int SER_Pin[2] = {1,2};   //pin 14 on the 75HC595
//int SER_Pin2 = 2;   //pin 14 on the 75HC595
int RCLK_Pin = 8;  //pin 12 on the 75HC595
int SRCLK_Pin = 12; //pin 11 on the 75HC595

//How many of the shift registers - change this
#define number_of_74hc595s 1 
#define rows 2 

//do not touch
//#define numOfRegisterPins number_of_74hc595s * 8
#define numOfRegisterPins 8

boolean registers[rows][numOfRegisterPins];
//boolean registers2[numOfRegisterPins];

void setup(){
  pinMode(SER_Pin[0], OUTPUT);
  pinMode(SER_Pin[1], OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);


  //reset all register pins
  clearRegisters();
  writeRegisters();
}               

//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     for (int j = 0; j<rows; j++){
      registers[j][i] = LOW;
     }
  }
} 

//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){

  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);
    for (int j=0; j<rows; j++){
      int val = registers[j][i];
      digitalWrite(SER_Pin[j], val);
    }     
    digitalWrite(SRCLK_Pin, HIGH);
    
  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int i, int j, int value){
  registers[i][j] = value;
//  if (register_num==1) registers[index] = value;
//  if (register_num==2) registers2[index] = value;
}


void loop(){
  
  setRegisterPin(0,0, HIGH);
  setRegisterPin(0,1, HIGH);
  setRegisterPin(0,2, LOW);
  setRegisterPin(0,3, HIGH);
  setRegisterPin(0,4, LOW);
  setRegisterPin(0,5, HIGH);
  setRegisterPin(0,6, LOW);
  setRegisterPin(0,7, HIGH);

  setRegisterPin(1,0, LOW);
  setRegisterPin(1,1, LOW);
  setRegisterPin(1,2, LOW);
  setRegisterPin(1,3, HIGH);
  setRegisterPin(1,4, LOW);
  setRegisterPin(1,5, HIGH);
  setRegisterPin(1,6, LOW);
  setRegisterPin(1,7, HIGH);  


  writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
  //Only call once after the values are set how you need.
}
