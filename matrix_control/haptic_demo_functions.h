void clear_all(){
//set all boolean valve states to LOW
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
      digitalWrite(SER_Pin[j], valve[i][j]);
    }     
    digitalWrite(SRCLK_Pin, HIGH);
    
  }
  digitalWrite(RCLK_Pin, HIGH);

}


void set(int i, int j, boolean value){
//set an individual valve boolean HIGH or LOW
  valve[i][j] = value;
//  if (register_num==1) valve[index] = value;
//  if (register_num==2) valve2[index] = value;
}

/*
void refreshScreen() {
  // updates states of the LEDs
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
*/

void number(int number_val,int pos_x,int pos_y){
//  Place braille letter at a position on the grid. (x,y) corresponds to
//  desired location of upper left dot of the braille letter.
//  Letters a-z correspond to case numbers 1-26. 0 is a space
  switch(number_val){
    //case 0 is just a blank 2x3 space
    case 1:
      valve[1][1]=HIGH;
      
      valve[2][0]=HIGH;
      valve[2][1]=HIGH;
      valve[2][2]=HIGH;
      valve[2][3]=HIGH;
      valve[2][4]=HIGH;
      valve[2][5]=HIGH;
      valve[2][6]=HIGH;
      
      valve[0][6]=HIGH;
      valve[1][6]=HIGH;
      valve[2][6]=HIGH;
      valve[3][6]=HIGH;
      valve[4][6]=HIGH;
      break;
    case 2:
     // horiz top
      valve[0][0]=HIGH;
      valve[1][0]=HIGH;
      valve[2][0]=HIGH;
      valve[3][0]=HIGH;
      valve[4][0]=HIGH;
      
      // horiz middle
      valve[0][3]=HIGH;
      valve[1][3]=HIGH;
      valve[2][3]=HIGH;
      valve[3][3]=HIGH;
      valve[4][3]=HIGH;
      
      // horiz bot
      valve[0][7]=HIGH;
      valve[1][7]=HIGH;
      valve[2][7]=HIGH;
      valve[3][7]=HIGH;
      valve[4][7]=HIGH;
      
      // vert top right
      valve[4][0]=HIGH;
      valve[4][1]=HIGH;  
      valve[4][2]=HIGH;  
      valve[4][3]=HIGH;
      
      //vert bot left
      valve[0][4]=HIGH;
      valve[0][5]=HIGH;  
      valve[0][6]=HIGH;  
      valve[0][7]=HIGH;  

      break;
    case 3:
      // horiz top
      valve[0][0]=HIGH;
      valve[1][0]=HIGH;
      valve[2][0]=HIGH;
      valve[3][0]=HIGH;
      valve[4][0]=HIGH;
      
      // horiz middle
      valve[0][3]=HIGH;
      valve[1][3]=HIGH;
      valve[2][3]=HIGH;
      valve[3][3]=HIGH;
      valve[4][3]=HIGH;
      
      // horiz bot
      valve[0][7]=HIGH;
      valve[1][7]=HIGH;
      valve[2][7]=HIGH;
      valve[3][7]=HIGH;
      valve[4][7]=HIGH;
      
      // vert right
      valve[4][0]=HIGH;
      valve[4][1]=HIGH;  
      valve[4][2]=HIGH;  
      valve[4][3]=HIGH;
      valve[4][4]=HIGH;
      valve[4][5]=HIGH;  
      valve[4][6]=HIGH;        
      break;
      
    case 4:
      // vert right
      valve[4][0]=HIGH;
      valve[4][1]=HIGH;  
      valve[4][2]=HIGH;  
      valve[4][3]=HIGH;
      valve[4][4]=HIGH;
      valve[4][5]=HIGH;  
      valve[4][6]=HIGH;
     
     // vert top left
      valve[0][0]=HIGH;
      valve[0][1]=HIGH;  
      valve[0][2]=HIGH;  
      valve[0][3]=HIGH;
     
     // horiz middle
      valve[0][3]=HIGH;
      valve[1][3]=HIGH;
      valve[2][3]=HIGH;
      valve[3][3]=HIGH;
      valve[4][3]=HIGH; 
          
      break;
    case 5:
      // horiz top
      valve[0][0]=HIGH;
      valve[1][0]=HIGH;
      valve[2][0]=HIGH;
      valve[3][0]=HIGH;
      valve[4][0]=HIGH;
      
      // horiz middle
      valve[0][3]=HIGH;
      valve[1][3]=HIGH;
      valve[2][3]=HIGH;
      valve[3][3]=HIGH;
      valve[4][3]=HIGH;
      
      // horiz bot
      valve[0][7]=HIGH;
      valve[1][7]=HIGH;
      valve[2][7]=HIGH;
      valve[3][7]=HIGH;
      valve[4][7]=HIGH;
      
      // vert top left
       valve[0][0]=HIGH;
       valve[0][1]=HIGH;
       valve[0][2]=HIGH;
       valve[0][3]=HIGH;
       
       //vert bot right
      valve[4][4]=HIGH;
      valve[4][5]=HIGH;  
      valve[4][6]=HIGH;  
      valve[4][7]=HIGH;
      
      break;
    case 6:
      // vert left
      valve[0][0]=HIGH;
      valve[0][1]=HIGH;  
      valve[0][2]=HIGH;  
      valve[0][3]=HIGH;
      valve[0][4]=HIGH;
      valve[0][5]=HIGH;  
      valve[0][6]=HIGH;
      
      // horiz top
       valve[0][0]=HIGH;
       valve[1][0]=HIGH;
       valve[2][0]=HIGH;
       valve[3][0]=HIGH;
       valve[4][0]=HIGH;
       
       // horiz middle
       valve[0][3]=HIGH;
       valve[1][3]=HIGH;
       valve[2][3]=HIGH;
       valve[3][3]=HIGH;
       valve[4][3]=HIGH;
       
       // horiz bot
       valve[0][7]=HIGH;
       valve[1][7]=HIGH;
       valve[2][7]=HIGH;
       valve[3][7]=HIGH;
       valve[4][7]=HIGH;
       
       //vert bot right
      valve[4][4]=HIGH;
      valve[4][5]=HIGH;  
      valve[4][6]=HIGH;  
      valve[4][7]=HIGH;
      break;
  }
}

void letter(int letter_val,int pos_x,int pos_y){
//  Place braille letter at a position on the grid. (x,y) corresponds to
//  desired location of upper left dot of the braille letter.
//  Letters a-z correspond to case numbers 1-26. 0 is a space
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
      current_letter="a";
      break;
    case 11:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="k";
      break;
    case 21:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      current_letter="u";
      break;
      
    case 2:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="b";
      break;
    case 12:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="l";
      break;
    case 22:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      current_letter="v";
      break;
      
    case 3:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="c";
      break;
    case 13:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="m";
      break;
    case 24:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      current_letter="x";
      break;
      
    case 4:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="d";
      break;
    case 14:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="n";
      break;
    case 25:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      current_letter="y";
      break;
      
    case 5:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="e";
      break;
    case 15:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="o";
      break;
    case 26:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= LOW; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH;
      current_letter="z";
      break;
      
    case 6:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="f";
      break;
    case 16:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="p";
      break;
    
    case 7:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="g";
      break;
    case 17:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="q";
      break;
      
    case 8:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="h";
      break;
    case 18:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= LOW;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="r";
      break;
      
    case 9:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="i";
      break;
    case 19:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= LOW;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="s";
      break;
    
    case 10:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="j";
      break;
    case 20:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= LOW;
      current_letter="t";
      break;
    
    case 23:
      valve[pos_x][pos_y]= LOW; valve[pos_x+1][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= LOW; valve[pos_x+1][pos_y+2]= HIGH;
      current_letter="w";
      break;

  }
}
