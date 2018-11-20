  
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
  #define DATA_PIN 4 // black
  #define CLK_PIN 3 // white
  // brown = ground
  // red = 5 V
  PS2Keyboard keyboard; 
  
  
// *****Initialize pins for valve array*****
  // For Arduino MEGA
  int SER_Pin[] = {43,41,39,37,35,33,31};  // pin31 is attached to the closest data pin to the PWR on the board
  int SRCLK_Pin = 45; //pin 11 on the 75HC595 - clock pin
  int RCLK_Pin = 47;  //pin 12 on the 75HC595 - latch pin (BOTTOM/OUTERMOST PIN on the board)
  
//  // For Arduino UNO
//  int SER_Pin[] = {11,10,9,8,7,6,5};  // pin5 is attached to the closest data pin to the PWR on the board
//  int SRCLK_Pin = 12; //pin 11 on the 75HC595 - clock pin
//  int RCLK_Pin = 13;  //pin 12 on the 75HC595 - latch pin (BOTTOM/OUTERMOST PIN on the board)
//  
  /*
  arrow[0] - up
  arrow[1] - right
  arrow[2] - down
  arrow[3] - left
  */
  
  // 2-dimensional array of row pin numbers for LEDs:
const int row[8] = {
  22, 24, 26, 28, 46, 48, 50, 52 };    // matrix pins 1, 2, 3, 4, 21, 22, 23, 24
const int col[8] = {
  30, 32, 34, 36, 38, 40, 42, 44 };    // matrix pins 5, 6, 7, 8, 9, 10, 11, 12   

  #define num_col 8
  #define num_row 7
  #define max_snake_length 30
  
  /*starting position*/
  int start_col = 4;
  int start_row = 3;
  int dir=4;
  unsigned long new_game_snake_speed = 1000;
  unsigned long snake_speed = new_game_snake_speed;
  unsigned long previousMillis = 0;  
  byte en=0;
  
  int mouse[2]={start_col,start_row};
  int snake[max_snake_length][2]; // saves the x and y positions of all the snake dots
  int snake_length;
  
  boolean valve[num_col][num_row];
  boolean got_the_mouse=LOW;
  boolean game_over=LOW;
  
  byte key_2;
  byte val_2;
  
  //// ************************************************ ////
  
  void setup(){
    Serial.begin(9600);
    keyboard.begin(DATA_PIN,CLK_PIN);
    randomSeed(analogRead(0));
    for (int i=0; i < num_row; i++){
      pinMode(SER_Pin[i], OUTPUT);
    }
    pinMode(RCLK_Pin, OUTPUT);
    pinMode(SRCLK_Pin, OUTPUT);
    
    for (int thisPin = 0; thisPin < 8; thisPin++) {
      // initialize the LED output pins:
      pinMode(col[thisPin], OUTPUT); 
      pinMode(row[thisPin], OUTPUT);  
      // take the col pins (i.e. the cathodes) high to ensure that
      // the LEDS are off: 
      digitalWrite(col[thisPin],LOW);   
      digitalWrite(row[thisPin],HIGH);
    }
  
    new_game();
  }      
  
  void loop(){
    while (game_over==LOW){
      unsigned long currentMillis = millis();
       
      snake_to_valves();
      update_valves();
      check_direction();
      check_mouse();
      check_collision();
      if (got_the_mouse==HIGH){
          snake_length=snake_length+1;
          got_the_mouse=LOW;
          snake_speed=snake_speed-50;
          
            clear_all();
            update_valves();
            delay(50);
            snake_to_valves();
            update_valves();
            delay(50);
      }
      if (currentMillis - previousMillis > snake_speed){
        movesnake();
        previousMillis = currentMillis;
//        Serial.println(snake_speed);
      }
      refreshScreen();
    }   
    delay(100);
    score();
    key_2 = keyboard.read();
    val_2 = key_2 - '0';
    if (val_2==240){
      new_game();
      delay(500);
    }   
  }  
  
  void refreshScreen() {
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

  void new_game(){
    clear_all();
    update_valves();
    mouse[0]=start_col;
    mouse[1]=start_row;
    snake[0][0]=start_col;
    snake[0][1]=start_row;
    while (mouse[0]==start_col && mouse[1]==start_row){
      mouse[0]=random(0,num_col);
      mouse[1]=random(0,num_row);
    }   
    snake_length=1;
    game_over=LOW;
    dir=4;
    snake_speed = new_game_snake_speed;
    previousMillis = 0;
  }
  
  void x(){
    valve[0][0]=HIGH;
    valve[1][1]=HIGH;
    valve[2][2]=HIGH;
    valve[3][3]=HIGH;
    valve[4][4]=HIGH;
    valve[5][5]=HIGH;
    valve[6][6]=HIGH;
    
    valve[6][0]=HIGH;
    valve[5][1]=HIGH;
    valve[4][2]=HIGH;
    valve[3][3]=HIGH;
    valve[2][4]=HIGH;
    valve[1][5]=HIGH;
    valve[0][6]=HIGH;
  }
  
  void score(){
    clear_all();
    int j=0;
    int k=0;
    for (int i=0; i < snake_length; i++){
      
      valve[j][k]=HIGH;
      j=j+1;
      if (j > 7) {
        j=0;
        k=k+1;
      }
      
    }
    update_valves();
  }
  
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
//  void update(){    
//    for(int i = 0; i < num_col; i++){
//     for (int j = 0; j < num_row; j++){
//       if(leds[i][j] == HIGH){
//         /*set all cols other than active to LOW*/
//         for(int k = 0; k < num_col; k++){
//          if(k != i) digitalWrite(col[k],LOW);
//         }
//         /*set active row to LOW*/
//         digitalWrite(row[j],LOW);
//         delay(1);
//         digitalWrite(row[j],HIGH);
//         all_high(); 
//         }
//     }
//    }    
//  }
  void clear_all(){
    for(int i = 0; i < num_col; i++){
       for (int j = 0; j < num_row; j++){
        valve[i][j] = LOW;
       }
    }
  }
  
  void snake_to_valves(){
    /*turns on leds corresponding to snake and mouse*/
    clear_all();
    valve[mouse[0]][mouse[1]]=HIGH;
    for (int i=0; i < snake_length; i++){
      valve[snake[i][0]][snake[i][1]]=HIGH;
    }
  }
  
  void shift_back(){
    /* Shifts the snake entries back to allow for a new head location
    Stores the previous snake so that when a mouse is eaten, the tail end stays put */   
    for (int i=snake_length-1; i >= 0; i--){
      snake[i+1][0]=snake[i][0];
      snake[i+1][1]=snake[i][1];
    }
 
  }
  void movesnake(){
    
    switch(dir){
      case 0:
        shift_back();
        snake[0][1]=snake[0][1]-1;
        break;
      case 1:
        shift_back();
        snake[0][0]=snake[0][0]+1;
        break;
      case 2:
        shift_back();
        snake[0][1]=snake[0][1]+1;
        break;
      case 3:
        shift_back();
        snake[0][0]=snake[0][0]-1;
        break;
      case 4:
        break;
    }
  }
  
  void check_mouse(){
    /*generates new mouse if snakehead eats mouse*/
    if (snake[0][0]==mouse[0] && snake[0][1]==mouse[1]){
      int new_mouse[2]={mouse[0],mouse[1]};
      /*make sure new mouse != old mouse*/
      while(new_mouse[0]==mouse[0] && new_mouse[1]==mouse[1]){
        new_mouse[0] = random(0,num_col);
        new_mouse[1] = random(0,num_row);
        // make sure the new mouse is not coincident with any part of the current snake
        for (int i=0; i < snake_length; i++){
          if (new_mouse[0]==snake[i][0] && new_mouse[1]==snake[i][1]){
            new_mouse[0]=mouse[0];
            new_mouse[1]=mouse[1];
          }
        }
      }
      mouse[0]=new_mouse[0];
      mouse[1]=new_mouse[1];
      got_the_mouse=HIGH;
//      snake_length=snake_length+1;
    }
    
  }
  
  int check_direction(){
    if(keyboard.available()){
      byte key = keyboard.read();
      byte val = key - '0';
      if(val==219) dir=0;
      if(val==229) dir=1;
      if(val==218) dir=2;
      if(val==216) dir=3;
    }
  }
  
  void check_collision(){
    /*check to see if snake head hits wall*/
    if (snake[0][0]>num_col-1 || snake[0][0]<0 || snake[0][1]>num_row-1 || snake[0][1] < 0){
      game_over=HIGH;
    }
    /*check to see if snake head hits rest of snake*/
    for (int i=1; i<snake_length;i++){
      if (snake[0][0]==snake[i][0] && snake[0][1]==snake[i][1]) game_over=HIGH;
    }
  }
  
//  void all_high(){
//    for(int i = 0; i < num_col; i++){
//       for (int j = 0; j < num_row; j++){
//        digitalWrite(col[i],HIGH);
//        digitalWrite(row[j],HIGH);
//       }
//    }
//  } 
  

