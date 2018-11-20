  
    /*
    ORDER OF PINS ON PCB
    
    RCLK_Pin
    SRCLK_Pin
    Row1
    Row2
    ...
    GND
    5V
    24V
    */
  
  #include <PS2Keyboard.h>
  PS2Keyboard keyboard; 
  
  const int DATA_PIN = 4; // black
  const int CLK_PIN = 3; // white
  //brown = ground
  //red = 5 V
  
  
  
  
  // 2-dimensional array of row pin numbers:
  const int row[8] = {
    22, 24, 26, 28, 46, 48, 50, 52 };    // matrix pins 1, 2, 3, 4, 21, 22, 23, 24
  const int col[8] = {
    30, 32, 34, 36, 38, 40, 42, 44 };    // matrix pins 5, 6, 7, 8, 9, 10, 11, 12   
  
  
  int SER_Pin[] = {11,10,9,8,7,6,5};  // pin5 is attached to the closest data pin to the PWR on the board
  int SRCLK_Pin = 12; //pin 11 on the 75HC595 - clock pin
  int RCLK_Pin = 13;  //pin 12 on the 75HC595 - latch pin (BOTTOM/OUTERMOST PIN on the board)
  
  #define num_col 8
  #define num_row 7
  
  int place = 0;
  int c;
  int x; 
  int y;
  
  boolean valve[num_col][num_row];
  
  
   //// ************************************************ ////
   
   
  void setup(){
    for (int i=0; i < num_row; i++){
      pinMode(SER_Pin[i], OUTPUT);
    }
    pinMode(RCLK_Pin, OUTPUT);
    pinMode(SRCLK_Pin, OUTPUT);
  
    for (int thisPin = 0; thisPin < 8; thisPin++) {
      // initialize the output pins:
      pinMode(col[thisPin], OUTPUT); 
      pinMode(row[thisPin], OUTPUT);  
      // take the col pins (i.e. the cathodes) high to ensure that
      // the LEDS are off: 
      digitalWrite(col[thisPin],LOW);   
      digitalWrite(row[thisPin],HIGH);
    }
  Serial.begin(9600);
    keyboard.begin(DATA_PIN,CLK_PIN);
    
    //reset all register pins
    clear_all();
    update_valves();
  }               
  
  void loop(){
//    while(keyboard.available()!=1){}
//    keyboard.read();
//    char key = keyboard.read();
  
    for(int j=0; j<num_row; j++){
      for(int i = 0; i < num_col; i++){
        while(Serial.read()!=10);
        clear_all();
        Serial.read();
        Serial.print("x = "); Serial.print(i); Serial.print(" ");
        Serial.print("y = "); Serial.println(j); 
        valve[i][j] = HIGH;
        update_valves();  
      }
    }
  }
  
  //set all register pins to LOW
  void clear_all(){
    for(int i = 0; i < num_col; i++){
       for (int j = 0; j < num_row; j++){
        valve[i][j] = LOW;
       }
    }
  } 
  
  void update_valves(){
  // updates the value of the solenoid valves to correspond to the boolean "valve"
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
  
  
  void refreshScreen() {
    // updates values of the LEDs
    for (int thisPin = 0; thisPin < 8; thisPin++) { 
      // makes sure the LEDS are off 
      digitalWrite(col[thisPin], LOW);   
      digitalWrite(row[thisPin], HIGH);
    }
  
    for (int x = 0; x < num_col; x++) {
      for (int y = 0; y < num_row; y++) {
        if (valve[x][y] == HIGH) {
          digitalWrite(col[x], HIGH);
          digitalWrite(row[y], LOW);
          digitalWrite(col[x], LOW);
          digitalWrite(row[y], HIGH);
        }
      }
    }
  }
  
  
  void letter(int letter_val,int pos_x,int pos_y){
  //  Place letter at a position on the grid. (x,y) corresponds to
  //  desired location of upper left dot of the letter.
    switch(letter_val){
      //case 0 is just a blank 2x3 space
      case 0:
        valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= LOW;
        valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
        valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
        break;
        
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
