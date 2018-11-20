  #include <PS2Keyboard.h>
  
  #define DATA_PIN 2
  #define CLK_PIN 3
  PS2Keyboard keyboard;
  
  int SER_Pin[] = {22,24,26,28,30,32,34}; //{0,1,2,3,4,5,6};  //pin 14 on the 75HC595 - data pins
  int RCLK_Pin = 31;  //pin 12 on the 75HC595 - latch pin (BOTTOM PIN)
  int SRCLK_Pin = 33; //pin 11 on the 75HC595 - clock pin

//  int row[] = {22,24,26,28,30};
//  int col[] = {0,1,2,3,4};
//  int arrow[] = {10,11,12,13};
//  boolean arrow_state[]={LOW,LOW,LOW,LOW};
  
  /*
  arrow[0] - up
  arrow[1] - right
  arrow[2] - down
  arrow[3] - left
  */
  
  #define num_col 8
  #define num_row 7
  #define max_snake_length 20
  
  /*starting position*/
  int start_col = 4;
  int start_row = 3;
  int dir=4;
  long snake_speed = 1000;
  long previousMillis = 0;  
  byte en=0;
  
  int mouse[2]={start_col,start_row};
  int snake[max_snake_length][2];
  int snake_length;
  
  boolean valve[num_col][num_row];
//  boolean leds[num_col][num_row];
  boolean got_the_mouse=LOW;
  boolean game_over=LOW;
  
  void setup(){
//    Serial.begin(9600);
//    keyboard.begin(DATA_PIN,CLK_PIN);
    keyboard.begin(DATA_PIN,CLK_PIN);
    randomSeed(analogRead(0));
//    for (int i=0; i < num_col; i++){
//      pinMode(col[i], OUTPUT);
//    }
//    for (int i=0; i < num_row; i++){
//      pinMode(row[i], OUTPUT);
//    }
    for (int i=0; i < num_row; i++){
      pinMode(SER_Pin[i], OUTPUT);
    }
    pinMode(RCLK_Pin, OUTPUT);
    pinMode(SRCLK_Pin, OUTPUT);

//    for (int i=0; i < 4; i++){
//      pinMode(arrow[i],INPUT);
//    }
    new_game();
  }      
  
  void loop(){
//    Serial.println(checkswitch());
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
          
//          for (int i=0; i<1; i++){
            clear_all();
            update_valves();
            delay(50);
            snake_to_valves();
            update_valves();
            delay(50);
//          }
      }
      if (currentMillis - previousMillis > snake_speed){
        movesnake();
        previousMillis = currentMillis;
      }
    }
    
    delay(100);
    clear_all();
    x();
    update_valves();
//    if(keyboard.available()){
//      long en = keyboard.read();
//    }
    byte key_2 = keyboard.read();
    byte val_2 = key_2 - '0';
    if (val_2==240){
      new_game();
      delay(500);
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
    snake_speed = 1000;
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
//  void clear_leds(){
//    for(int i = 0; i < num_col; i++){
//       for (int j = 0; j < num_row; j++){
//        leds[i][j]=LOW;
//       }
//    }
//  } 
  
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
  
//  void all_high(){
//    for(int i = 0; i < num_col; i++){
//       for (int j = 0; j < num_row; j++){
//        digitalWrite(col[i],HIGH);
//        digitalWrite(row[j],HIGH);
//       }
//    }
//  } 
  int check_direction(){
    if(keyboard.available()){
      byte key = keyboard.read();
      byte val = key - '0';
      if(val==219) dir=0;
      if(val==229) dir=1;
      if(val==218) dir=2;
      if(val==216) dir=3;
      
//      if(val==PS2_UPARROW) dir=0;
//      if(val==PS2_RIGHTARROW) dir=1;
//      if(val==PS2_DOWNARROW) dir=2;
//      if(val==PS2_LEFTARROW) dir=3;
    }
  }
  
//  int check_direction(){
//    for (int i=0; i<4; i++){
//      if (arrow_state[0]==LOW && arrow_state[1]==LOW && arrow_state[2]==LOW && arrow_state[3]==LOW){
//        if (digitalRead(arrow[i])==HIGH){
//          arrow_state[i]=HIGH;
//          dir=i;
//          return i;
//        }
//      }
//      else if (digitalRead(arrow[i])==LOW){
//          arrow_state[i]=LOW;         
//      }
//    }
//    return 4;   
//  }
  
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
  
  
  

