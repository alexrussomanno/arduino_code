  
  int row[] = {22,24,26,28,30};
  int col[] = {0,1,2,3,4};
  int arrow[] = {8,9,10,11};
  boolean arrow_state[]={LOW,LOW,LOW,LOW};
  /*
  arrow[0] - up
  arrow[1] - right
  arrow[2] - down
  arrow[3] - left
  */
  
  #define num_col 5
  #define num_row 5
  #define max_snake_length 10
  
  /*starting position*/
  int start_col = 2;
  int start_row = 2;
  boolean button_in=LOW;
  int dir=4;
//  int time_step=1000;
  long snake_speed = 1000;
  long previousMillis = 0;  
//  int time;
  int mouse[]={4,1};
//  int snakehead[]={cur_col,cur_row};
//  int snaketail[2];
  int previous_tail[2];
  int snake[max_snake_length][2];
//  int newsnake[10][2];
  int snake_length;
  boolean leds[num_col][num_row];
  boolean got_the_snake=LOW;
  
  void setup(){
//    Serial.begin(9600);
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
    snake[0][0]=start_col;
    snake[0][1]=start_row;
   
    snake_length=1;
  }      
  
  void loop(){
//    Serial.println(checkswitch());
    unsigned long currentMillis = millis();
    clear_leds();
    snake_to_leds();
    update();
//    leds[cur_col][cur_row]=HIGH;
//    delay(100);
//    while(checkswitch()==4);    
    checkswitch();
    mouse_check();
    if (currentMillis - previousMillis > snake_speed){
//      int snake_tail[2]={snake[snake_length][0],snake[snake_length][1]};
      if (got_the_snake==HIGH){
        snake_length=snake_length+1;
        got_the_snake=LOW;
      }
      movesnake();
            
      previousMillis = currentMillis;
//      Serial.println(snake_length);
    }
    
//    leds[cur_col][cur_row]=HIGH;
//    
    
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
    leds[mouse[0]][mouse[1]]=HIGH;
    for (int i=0; i < snake_length; i++){
      leds[snake[i][0]][snake[i][1]]=HIGH;
    }
  }
  void advance(){
    /*activate this before the snake head moves*/
    if (got_the_snake==LOW){
      for (int i=snake_length-1; i > 0; i--){
        snake[i][0]=snake[i-1][0];
        snake[i][1]=snake[i-1][1];
      }
    }
    else{
      for (int i=snake_length-1; i > 0; i--){
        snake[i][0]=snake[i-1][0];
        snake[i][1]=snake[i-1][1];
      }
    }
    
  }
  void movesnake(){
    
    switch(dir){
      case 0:
        advance();
        snake[0][1]=snake[0][1]-1;
        break;
      case 1:
        advance();
        snake[0][0]=snake[0][0]+1;
        break;
      case 2:
        advance();
        snake[0][1]=snake[0][1]+1;
        break;
      case 3:
        advance();
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
      got_the_snake=HIGH;
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
  
      
  //  switch(checkswitch()){
  //    case 0:
  //      leds[cur_col][cur_row]=LOW;
  //      cur_row=cur_row-1;
  //      break;
  //    case 1:
  //      leds[cur_col][cur_row]=LOW;
  //      cur_col=cur_col+1;
  //      break;
  //    case 2:
  //      leds[cur_col][cur_row]=LOW;
  //      cur_row=cur_row+1;
  //      break;
  //    case 3:
  //      leds[cur_col][cur_row]=LOW;
  //      cur_col=cur_col-1;
  //      break;
  //    case 4:
  //      break;
  //  }
  
  

