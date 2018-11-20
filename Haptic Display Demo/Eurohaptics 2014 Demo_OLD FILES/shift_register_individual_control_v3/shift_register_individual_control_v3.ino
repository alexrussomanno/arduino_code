  int SER_Pin[] = {22,24,26,28,30,32,34}; //{0,1,2,3,4,5,6};  //pin 14 on the 75HC595 - data pins
  int RCLK_Pin = 38;  //pin 12 on the 75HC595 - latch pin (BOTTOM PIN)
  int SRCLK_Pin = 40; //pin 11 on the 75HC595 - clock pin

  int a = 1; int b = 2; int c = 3; int d = 4; int e = 5; int f = 6; 
  int g = 7;  int h = 8;  int i = 9;  int j = 10; int k = 11; int l = 12; 
  int m = 13; int n = 14; int o = 15; int p = 16; int q = 17; int r = 18; 
  int s = 19; int t = 20; int u = 21; int v = 22; int w = 23; int x = 24; 
  int y = 25; int z = 26;

//How many of the shift valve - change this
//#define number_of_74hc595s 1 
//#define rows 3 
//int rows = 3;
//do not touch
//#define numOfRegisterPins number_of_74hc595s * 8
#define num_col 8
#define num_row 7

boolean valve[num_col][num_row];

void setup(){
  for (int i=0; i < num_row; i++){
    pinMode(SER_Pin[i], OUTPUT);
  }
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);


  //reset all register pins
  clear_all();
  update_valves();
}               

//set all register pins to LOW
void clear_all(){
  for(int i = 0; i < num_col; i++){
     for (int j = 0; j < num_row; j++){
      valve[i][j] = LOW;
     }
  }
} 

//Set and display valve
//Only call AFTER all values are set how you would like (slow otherwise)
void update_valves(){

  digitalWrite(RCLK_Pin, LOW);

  for(int i = num_col - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);
    for (int j = 0; j < num_row; j++){
      int val = valve[i][j];
      digitalWrite(SER_Pin[j], val);
    }     
    digitalWrite(SRCLK_Pin, HIGH);
    
  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void set(int i, int j, boolean value){
  valve[i][j] = value;
//  if (register_num==1) valve[index] = value;
//  if (register_num==2) valve2[index] = value;
}

void loop(){
  for (int ii=1; ii<=26; ii++){
    letter(ii,0,0);
    update_valves();
    delay(500);
    clear_all();
  }



  /* Set each row all high 1 by 1 */
//  for (int j=0; j<num_row; j++){
//    for (int i=0; i<num_col; i++){
//      set(i,j,HIGH);
//      update_valves();
//            
//    }
//    delay(2000);
//    clear_all();
//  }
  
  /*Set a certain pin high*/
//  int col = 3;
//  int row = 0;
//  set(col,row,HIGH);
//  update_valves();
    
}

void letter(int letter_val,int pos_x,int pos_y){
//  Place letter at a position on the grid. (x,y) corresponds to
//  desired location of upper left dot of the letter.
  switch(letter_val){
    case 1:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 11:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 21:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 2:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 12:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 22:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 3:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 13:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 24:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 4:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 14:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 25:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 5:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 15:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 26:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      break;
      
    case 6:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 16:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    
    case 7:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 17:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
      
    case 8:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 18:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
      
    case 9:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 19:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    
    case 10:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      break;
    case 20:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      break;
    
    case 23:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= HIGH;
      break;

  }
}
