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
      int val = valve[i][j];
      digitalWrite(SER_Pin[j], val);
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
    case 27:
      valve[pos_x][pos_y]= HIGH; valve[pos_x+1][pos_y]= HIGH; valve[pos_x+2][pos_y]= HIGH;
      valve[pos_x][pos_y+1]= HIGH; valve[pos_x+1][pos_y+1]= HIGH; valve[pos_x+2][pos_y+1]= HIGH;
      valve[pos_x][pos_y+2]= HIGH; valve[pos_x+1][pos_y+2]= HIGH; valve[pos_x+2][pos_y+2]= HIGH;
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
