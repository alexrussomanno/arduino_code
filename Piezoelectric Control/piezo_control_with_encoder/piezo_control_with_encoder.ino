  #define CH_A 19            // Encoder Channel A - This pin can call an ISR on Arduino Mega
  #define CH_B 18            // Encoder Channel B - This pin can call an ISR on Arduino Mega

  int dot[]={0,24,28,32,22,26,30,36,34};
  volatile int encPos=0;
  int a = 1; int b = 2; int c = 3; int d = 4; int e = 5; int f = 6; 
  int g = 7;  int h = 8;  int i = 9;  int j = 10; int k = 11; int l = 12; 
  int m = 13; int n = 14; int o = 15; int p = 16; int q = 17; int r = 18; 
  int s = 19; int t = 20; int u = 21; int v = 22; int w = 23; int x = 24; 
  int y = 25; int z = 26;
  
  void setup(){
    pinMode(CH_A, INPUT);
    pinMode(CH_B, INPUT);    
    attachInterrupt(4, readEncoderA,CHANGE);
    attachInterrupt(5, readEncoderB, CHANGE);
    
    for (int i=1;i<9;i++){
      pinMode(dot[i],OUTPUT);
    }  
    delay(1000);
    Serial.begin(9600);
    
  }
  
  void loop(){
    alternating();
    
  }
  
  void alternating(){
    /*Alternates between all pins up and all pins down every centimeter
    call using alternating(encPos);*/
    if (encPos>-100  & encPos<=184+490*0) all_up();  if (encPos>184+490*0 & encPos<=490*1) all_down();
    if (encPos>490*1 & encPos<=184+490*1) all_up();  if (encPos>184+490*1 & encPos<=490*2) all_down();
    if (encPos>490*2 & encPos<=184+490*2) all_up();  if (encPos>184+490*2 & encPos<=490*3) all_down();
    if (encPos>490*3 & encPos<=184+490*3) all_up();  if (encPos>184+490*3 & encPos<=490*4) all_down();
    if (encPos>490*4 & encPos<=184+490*4) all_up();  if (encPos>184+490*4 & encPos<=490*5) all_down();
    if (encPos>490*5 & encPos<=184+490*5) all_up();  if (encPos>184+490*5 & encPos<=490*6) all_down();
    if (encPos>490*6 & encPos<=184+490*6) all_up();  if (encPos>184+490*6 & encPos<=490*7) all_down();
    if (encPos>490*7 & encPos<=184+490*7) all_up();  if (encPos>184+490*7 & encPos<=490*8) all_down();
    if (encPos>490*8 & encPos<=184+490*8) all_up();  if (encPos>184+490*8 & encPos<=490*9) all_down();
    if (encPos>490*9 & encPos<=184+490*9) all_up();  if (encPos>184+490*9 & encPos<=490*10) all_down();
    if (encPos>490*10 & encPos<=184+490*10) all_up();  if (encPos>184+490*10 & encPos<=490*11) all_down();
    if (encPos>490*11 & encPos<=184+490*11) all_up();  if (encPos>184+490*11 & encPos<=490*12) all_down();
    if (encPos>490*12 & encPos<=184+490*12) all_up();  if (encPos>184+490*12 & encPos<=490*13) all_down();
    if (encPos>490*13 & encPos<=184+490*13) all_up();  if (encPos>184+490*13 & encPos<=490*14) all_down();
    if (encPos>490*14 & encPos<=184+490*14) all_up();  if (encPos>184+490*14 & encPos<=490*15) all_down();
    if (encPos>490*15 & encPos<=184+490*15) all_up();  if (encPos>184+490*15 & encPos<=490*16) all_down();
    if (encPos>490*16 & encPos<=184+490*16) all_up();  if (encPos>184+490*16 & encPos<=490*17) all_down();
    if (encPos>490*17 & encPos<=184+490*17) all_up();  if (encPos>184+490*17 & encPos<=490*18) all_down();
    if (encPos>490*18 & encPos<=184+490*18) all_up();  if (encPos>184+490*18 & encPos<=490*19) all_down();
    if (encPos>490*19 & encPos<=184+490*19) all_up();  if (encPos>184+490*19 & encPos<=490*20) all_down();
    if (encPos>490*20 & encPos<=184+490*20) all_up();  if (encPos>184+490*20 & encPos<=490*21) all_down();
    if (encPos>490*21 & encPos<=184+490*21) all_up();  if (encPos>184+490*21 & encPos<=490*22) all_down();
    if (encPos>490*22 & encPos<=184+490*22) all_up();  if (encPos>184+490*22 & encPos<=490*23) all_down();
    if (encPos>490*23 & encPos<=184+490*23) all_up();  if (encPos>184+490*23 & encPos<=490*24) all_down();
    if (encPos>490*24 & encPos<=184+490*24) all_up();  if (encPos>184+490*24 & encPos<=490*25) all_down();
    if (encPos>490*25 & encPos<=184+490*25) all_up();  if (encPos>184+490*25 & encPos<=490*26) all_down();
    if (encPos>490*26 & encPos<=184+490*26) all_up();  if (encPos>184+490*26 & encPos<=490*27) all_down();
    if (encPos>490*27 & encPos<=184+490*27) all_up();  if (encPos>184+490*27 & encPos<=490*28) all_down();
    if (encPos>490*28 & encPos<=184+490*28) all_up();  if (encPos>184+490*28 & encPos<=490*29) all_down();
    if (encPos>490*29 & encPos<=184+490*29) all_up();  if (encPos>184+490*29 & encPos<=490*30) all_down();
    if (encPos>490*30 & encPos<=184+490*30) all_up();  if (encPos>184+490*30 & encPos<=490*31) all_down();
    if (encPos>490*31 & encPos<=184+490*31) all_up();  if (encPos>184+490*31 & encPos<=490*32) all_down();
    if (encPos>490*32) all_down();

  }
  
  int rand_letter(){
    int randNum=random(1,27);
    return randNum;
  }  
  
  void readEncoderA(){
    if(digitalRead(CH_A) ^ digitalRead(CH_B))
      encPos--;
    else
      encPos++;
  }
  
  void readEncoderB(){
    if(digitalRead(CH_A) ^ digitalRead(CH_B))
      encPos++;
    else
      encPos--;
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
  
  
  

