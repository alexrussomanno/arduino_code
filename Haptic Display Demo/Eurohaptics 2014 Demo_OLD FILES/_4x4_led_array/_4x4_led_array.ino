  
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
  #define max_snake_length 15
  int cur_col = random(0,num_col);
  int cur_row = random(0,num_row);
  boolean button_in=LOW;
//  long randNumber;
  int dir=4;
  int time_step=500;
  int time;
  int mouse[2];
  int snakehead[]={cur_col,cur_row};
  int snaketail[2];
 
  int snake[max_snake_length][2];
  int newsnake[10][2];
  int snake_length;
  boolean leds[num_col][num_row];
  
  void setup(){
    
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
    leds[cur_col][cur_row]=HIGH;
    time=millis();
//    Serial.begin(9600);
  }      
  
  void loop(){
//    Serial.println(checkswitch());
    update();
    leds[cur_col][cur_row]=HIGH;
//    delay(100);
//    while(checkswitch()==4);
    
    checkswitch();
    if (millis()>=time+time_step){
      switch(dir){
        case 0:
//          dir=0;
          leds[cur_col][cur_row]=LOW;
          cur_row=cur_row-1;
          break;
        case 1:
//          dir=1;
          leds[cur_col][cur_row]=LOW;
          cur_col=cur_col+1;
          break;
        case 2:
//          dir=2;
          leds[cur_col][cur_row]=LOW;
          cur_row=cur_row+1;
          break;
        case 3:
//          dir=3;
          leds[cur_col][cur_row]=LOW;
          cur_col=cur_col-1;
          break;
        case 4:
          break;
      }
      time=millis();
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
  
  void generate_mouse(){
    /*generates new mouse if snakehead eats mouse*/
    if (snakehead[0]==mouse[0] && snakehead[1]==mouse[1]){
      int new_mouse[]={mouse[0],mouse[1]};
      /*make sure new mouse != old mouse*/
      while(new_mouse[0]==mouse[0] && new_mouse[1]==mouse[1]){
        int new_mouse[0] = random(0,num_col);
        int new_mouse[1] = random(0,num_row);
        for (int i=0; i < max_snake_length; i++){
          if (new_mouse[0]==snake[i][0] && new_mouse[1]==snake[i][1]){
            new_mouse[0]=mouse[0];
            new_mouse[1]=mouse[1];
          }
        }
      }
      int mouse[2]={new_mouse_x,new_mouse_y};
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
  
  

