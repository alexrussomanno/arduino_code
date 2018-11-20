  
  int row[] = {22,24,26,28,30,32,34,36};
  int col[] = {0,1,2,3,4,5,6,7};
  int arrow[] = {8,9,10,11};
  boolean arrow_state[]={LOW,LOW,LOW,LOW};
  /*
  arrow[0] - up
  arrow[1] - right
  arrow[2] - down
  arrow[3] - left
  */
  
  #define num_col 8
  #define num_row 8
  #define max_snake_length 20
  
  /*starting position*/
  int start_col = 4;
  int start_row = 4;
  int dir=4;
  long snake_speed = 1000;
  long previousMillis = 0;  
  
  int mouse[]={start_col,start_row};
  int snake[max_snake_length][2];
  int snake_length;
  
  boolean leds[num_col][num_row];
  boolean got_the_mouse=LOW;
  boolean game_over=LOW;
  
  void setup(){
//    Serial.begin(9600);
    randomSeed(analogRead(0));
    for (int i=0; i < num_col; i++){
      pinMode(col[i], OUTPUT);
    }
    for (int i=0; i < num_row; i++){
      pinMode(row[i], OUTPUT);
    }
    for (int i=0; i < 4; i++){
      pinMode(arrow[i],INPUT);
    }
    all_high();
    clear_leds();
    new_game();
  }      
  
  void loop(){
//    Serial.println(checkswitch());
    while (game_over==LOW){
      unsigned long currentMillis = millis();    
      snake_to_leds();
      update();
      checkswitch();
      mouse_check();
      check_collision();
      if (got_the_mouse==HIGH){
          snake_length=snake_length+1;
          got_the_mouse=LOW;
          snake_speed=snake_speed-50;
      }
      if (currentMillis - previousMillis > snake_speed){
        movesnake();
        previousMillis = currentMillis;
      }
    }
    
    delay(100);
    clear_leds();
    leds[0][0]=HIGH;
    leds[1][1]=HIGH;
    leds[2][2]=HIGH;
    leds[3][3]=HIGH;
    leds[4][4]=HIGH;
    leds[0][4]=HIGH;
    leds[1][3]=HIGH;
//    leds[2][2]=HIGH;
    leds[3][1]=HIGH;
    leds[4][0]=HIGH;
    update();
    if (digitalRead(arrow[0])==HIGH){
      new_game();
      delay(500);
    }   
  }  
  
  void new_game(){
    int mouse[]={start_col,start_row};
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
  
  void update(){    
    for(int i = 0; i < num_col; i++){
     for (int j = 0; j < num_row; j++){
       if(leds[i][j] == HIGH){
         /*set all cols other than active to LOW*/
         for(int k = 0; k < num_col; k++){
          if(k != i) digitalWrite(col[k],LOW);
         }
         /*set active row to LOW*/
         digitalWrite(row[j],LOW);
         delay(1);
         digitalWrite(row[j],HIGH);
         all_high(); 
         }
     }
    }    
  }
  
  void clear_leds(){
    for(int i = 0; i < num_col; i++){
       for (int j = 0; j < num_row; j++){
        leds[i][j]=LOW;
       }
    }
  } 
  
  void snake_to_leds(){
    /*turns on leds corresponding to snake and mouse*/
    clear_leds();
    leds[mouse[0]][mouse[1]]=HIGH;
    for (int i=0; i < snake_length; i++){
      leds[snake[i][0]][snake[i][1]]=HIGH;
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
  
  void mouse_check(){
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
  
  void all_high(){
    for(int i = 0; i < num_col; i++){
       for (int j = 0; j < num_row; j++){
        digitalWrite(col[i],HIGH);
        digitalWrite(row[j],HIGH);
       }
    }
  } 
  
  int checkswitch(){
    for (int i=0; i<4; i++){
      if (arrow_state[0]==LOW && arrow_state[1]==LOW && arrow_state[2]==LOW && arrow_state[3]==LOW){
        if (digitalRead(arrow[i])==HIGH){
          arrow_state[i]=HIGH;
          dir=i;
          return i;
        }
      }
      else if (digitalRead(arrow[i])==LOW){
          arrow_state[i]=LOW;         
      }
    }
    return 4;   
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
  
  
  

