  // type(a) activates the pins on the piezoelectric to output the letter "a"\
  
  // Creates an array for the braille dots (1-8). There is a 0 in the first entry because it is 
  // zero indexed and there is no 0 braille dot.
  
  // Braill dot numbering:
  //      1 4
  //      2 5
  //      3 6
  //      7 8
  
  // Plug ribbon cable in from 22 to 36 on the arduino
  int dot[]={0,24,28,32,22,26,30,36,34};
//  int dot[]={0,40,46,50,38,42,48,36,34};
//  22 24 26 26 28 30 32
//  38 40 42 44 46 48 50
  // Associates alphabet with numbers for use in "type" function
  int a = 1; int b = 2; int c = 3; int d = 4; int e = 5; int f = 6; 
  int g = 7;  int h = 8;  int i = 9;  int j = 10; int k = 11; int l = 12; 
  int m = 13; int n = 14; int o = 15; int p = 16; int q = 17; int r = 18; 
  int s = 19; int t = 20; int u = 21; int v = 22; int w = 23; int x = 24; 
  int y = 25; int z = 26;
  

  
  void setup(){
    for (int i=1;i<9;i++){
      pinMode(dot[i],OUTPUT);
    }
    Serial.begin(9600);
    
  }
  
  void loop(){
//    delay(1040);
//    all_up();
//    delay(1040);
//    all_down();
    all_up();
//    digitalWrite(dot[3],HIGH);
    delay(2040);
    all_down();
//    digitalWrite(dot[3],LOW);
    delay(2040);
//    haptix(pos);
  }
  
  void all_down(){
      digitalWrite(dot[1],LOW); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      digitalWrite(dot[7],LOW); digitalWrite(dot[8],LOW);
  }

  void all_up(){
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
      digitalWrite(dot[7],HIGH); digitalWrite(dot[8],HIGH);
  }
  
  void type(int letter){

  switch(letter){
    case 1: //a
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
    case 2: //b
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
    case 3: //c
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
    case 4: //d
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
    case 5: //e
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
    case 6: //f
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
    case 7: //g
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
    case 8: //h
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
      break;
    case 9: //i
      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
    case 10: //j
      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
      break;
    case 11: //k
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
      break;
    case 12: //l
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
      break;
    case 13: //m
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);;
      break;
    case 14: //n
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
      break;
    case 15: //o
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
      break;
    case 16: //p:
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
      break;
    case 17: //q:
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
      break;
    case 18: //r:
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
      break;
    case 19: //s:
      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
      break;
    case 20: //t:
      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
      break;
    case 21: //u:
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
      break;
    case 22: //v:
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
      break;
    case 23: //w:
      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],LOW); digitalWrite(dot[6],HIGH);
      break;
    case 24: //x:
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
      break;
    case 25: //y:
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
      break;
    case 26: //z:
      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
      break;
      
    }
  }
  void print_letter(int letter){
    if(letter == 1) Serial.print('a');
    if(letter == 2) Serial.print('b');
    if(letter == 3) Serial.print('c');
    if(letter == 4) Serial.print('d');
    if(letter == 5) Serial.print('e');
    if(letter == 6) Serial.print('f');
    if(letter == 7) Serial.print('g');
    if(letter == 8) Serial.print('h');
    if(letter == 9) Serial.print('i');
    if(letter == 10) Serial.print('j');
    if(letter == 11) Serial.print('k');
    if(letter == 12) Serial.print('l');
    if(letter == 13) Serial.print('m');
    if(letter == 14) Serial.print('n');
    if(letter == 15) Serial.print('o');
    if(letter == 16) Serial.print('p');
    if(letter == 17) Serial.print('q');
    if(letter == 18) Serial.print('r');
    if(letter == 19) Serial.print('s');
    if(letter == 20) Serial.print('t');
    if(letter == 21) Serial.print('u');
    if(letter == 22) Serial.print('v');
    if(letter == 23) Serial.print('w');
    if(letter == 24) Serial.print('x');
    if(letter == 25) Serial.print('y');
    if(letter == 26) Serial.print('z');  
  }
