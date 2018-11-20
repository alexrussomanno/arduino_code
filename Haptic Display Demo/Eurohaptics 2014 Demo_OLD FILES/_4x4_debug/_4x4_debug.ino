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
  int cur_col = random(0,num_col);
  int cur_row = random(0,num_row);
  boolean button_in=LOW;
//  long randNumber;
  int dir=4;
  int time_step=500;
  int time;
  int mouse[]={1,1};
  int snakehead[]={cur_col,cur_row};
  int snaketail[2];
  int snake[10][2];
  int newsnake[10][2];
  int snake_length;
  boolean leds[num_col][num_row];

  void setup(){
    
    for (int i=0; i < num_col; i++){
      pinMode(col[i], OUTPUT);
    }
    for (int i=0; i< num_row; i++){
      pinMode(row[i], OUTPUT);
    }
    Serial.begin(9600);
//    all_high();
//    clear_leds();
  }      
  
  void loop(){
    Serial.println(sizeof(snake));
    delay(200);
//    digitalWrite(col[1],LOW);
//    digitalWrite(col[2],LOW);
//    digitalWrite(col[3],LOW);
//    digitalWrite(col[4],LOW);
//    
//    digitalWrite(row[1],LOW);
//    delay(1);
//    digitalWrite(row[1],HIGH);
//    delay(1);
//    all_high();
  }
  
  void all_high(){
    for(int i = 0; i < num_col; i++){
       for (int j = 0; j < num_row; j++){
        digitalWrite(col[i],HIGH);
        digitalWrite(row[j],HIGH);
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
