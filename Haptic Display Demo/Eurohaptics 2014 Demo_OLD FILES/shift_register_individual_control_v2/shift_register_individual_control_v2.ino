int SER_Pin[] = {1,2,3};   //pin 14 on the 75HC595
//int SER_Pin2 = 2;   //pin 14 on the 75HC595
int RCLK_Pin = 8;  //pin 12 on the 75HC595
int SRCLK_Pin = 9; //pin 11 on the 75HC595

//How many of the shift registers - change this
#define number_of_74hc595s 1 
//#define rows 3 
int rows = 3;
//do not touch
//#define numOfRegisterPins number_of_74hc595s * 8
#define numOfRegisterPins 8

boolean registers[3][numOfRegisterPins];
//boolean registers2[numOfRegisterPins];

void setup(){
  pinMode(SER_Pin[0], OUTPUT);
  pinMode(SER_Pin[1], OUTPUT);
  pinMode(SER_Pin[2], OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);


  //reset all register pins
  clearRegisters();
  writeRegisters();
}               

//set all register pins to LOW
void clearRegisters(){
  for(int j = numOfRegisterPins - 1; j >=  0; j--){
     for (int i = 0; i<rows; i++){
      registers[i][j] = LOW;
     }
  }
} 

//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){

  digitalWrite(RCLK_Pin, LOW);

  for(int j = numOfRegisterPins - 1; j >=  0; j--){
    digitalWrite(SRCLK_Pin, LOW);
    for (int i = 0; i < rows; i++){
      int val = registers[i][j];
      digitalWrite(SER_Pin[i], val);
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

  letter('H',0,0);
  letter('A',0,3);
  letter('P',0,6);

//  setRegisterPin(0,0, HIGH);
//  setRegisterPin(0,1, HIGH);
//  setRegisterPin(0,2, LOW);
//  setRegisterPin(0,3, HIGH);
//  setRegisterPin(0,4, LOW);
//  setRegisterPin(0,5, HIGH);
//  setRegisterPin(0,6, LOW);
//  setRegisterPin(0,7, HIGH);
//
//  setRegisterPin(1,0, LOW);
//  setRegisterPin(1,1, LOW);
//  setRegisterPin(1,2, LOW);
//  setRegisterPin(1,3, HIGH);
//  setRegisterPin(1,4, LOW);
//  setRegisterPin(1,5, HIGH);
//  setRegisterPin(1,6, LOW);
//  setRegisterPin(1,7, HIGH);  
//
//  setRegisterPin(2,0, LOW);
//  setRegisterPin(2,1, LOW);
//  setRegisterPin(2,2, LOW);
//  setRegisterPin(2,3, LOW);
//  setRegisterPin(2,4, LOW);
//  setRegisterPin(2,5, HIGH);
//  setRegisterPin(2,6, LOW);
//  setRegisterPin(2,7, HIGH);

  writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
  //Only call once after the values are set how you need.
}

void letter(char letter_val,int pos_x,int pos_y){
//  Place letter at a position on the grid. (x,y) corresponds to
//  desired location of upper left dot of the letter.
  switch(letter_val){
    case 'A':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'K':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'U':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= HIGH;
      break;
      
    case 'B':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'L':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'V':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= HIGH;
      break;
      
    case 'C':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'M':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'X':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= HIGH;
      break;
      
    case 'D':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'N':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'Y':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= HIGH;
      break;
      
    case 'E':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'O':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'Z':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= LOW; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= HIGH;
      break;
      
    case 'F':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'P':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
    
    case 'G':
     registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'Q':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
      
    case 'H':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'R':
      registers[pos_x][pos_y]= HIGH; registers[pos_x][pos_y+1]= LOW;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
      
    case 'I':
      registers[pos_x][pos_y]= LOW; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'S':
      registers[pos_x][pos_y]= LOW; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= LOW;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
    
    case 'J':
      registers[pos_x][pos_y]= LOW; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= LOW;
      break;
    case 'T':
      registers[pos_x][pos_y]= LOW; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= HIGH; registers[pos_x+2][pos_y+1]= LOW;
      break;
    
    case 'W':
      registers[pos_x][pos_y]= LOW; registers[pos_x][pos_y+1]= HIGH;
      registers[pos_x+1][pos_y]= HIGH; registers[pos_x+1][pos_y+1]= HIGH;
      registers[pos_x+2][pos_y]= LOW; registers[pos_x+2][pos_y+1]= HIGH;
      break;

  }
}
