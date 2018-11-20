  int dot[]={0,24,28,32,22,26,30,36,34};
  int a = 1; int b = 2; int c = 3; int d = 4; int e = 5; int f = 6; 
  int g = 7;  int h = 8;  int i = 9;  int j = 10; int k = 11; int l = 12; 
  int m = 13; int n = 14; int o = 15; int p = 16; int q = 17; int r = 18; 
  int s = 19; int t = 20; int u = 21; int v = 22; int w = 23; int x = 24; 
  int y = 25; int z = 26;
  
  void setup(){
    for (int i=1;i<9;i++){
      pinMode(dot[i],OUTPUT);
    }
//    pinMode(blinker,OUTPUT);
    Serial.begin(9600);
    
  }
  
  void loop(){
//    delay(1040);
//    all_up();
//    delay(1040);
//    all_down();
    type(a);
    delay(1000);
    type(e);
    delay(1000);
//    haptix(pos);
  }
  
  void alternating(int pos){
    /*Alternates between all pins up and all pins down every centimeter
    call using alternating(pos);*/
    if (pos>24 & pos<=24+104) all_up();
    if (pos>24+104*1 & pos<=24+104*2) all_down();
    if (pos>24+104*2 & pos<=24+104*3) all_up();
    if (pos>24+104*3 & pos<=24+104*4) all_down();
    if (pos>24+104*4 & pos<=24+104*5) all_up();
    if (pos>24+104*5 & pos<=24+104*6) all_down();
    if (pos>24+104*6 & pos<=24+104*7) all_up();
    if (pos>24+104*7 & pos<=24+104*8) all_down();
    if (pos>24+104*8) all_up();

  }
  
  void haptix(int pos){
    if (pos>24+104*0 & pos<=24+104*0+104/4) type('h');
    if (pos>24+104*0+104/4 & pos<=24+104*1) all_down();
    
    if (pos>24+104*1 & pos<=24+104*1+104/4) type('a');
    if (pos>24+104*1+104/4 & pos<=24+104*2) all_down();
    
    if (pos>24+104*2 & pos<=24+104*2+104/4) type('p');
    if (pos>24+104*2+104/4 & pos<=24+104*3) all_down();
    
    if (pos>24+104*3 & pos<=24+104*3+104/4) type('t');
    if (pos>24+104*3+104/4 & pos<=24+104*4) all_down();
    
    if (pos>24+104*4 & pos<=24+104*4+104/4) type('i');
    if (pos>24+104*4+104/4 & pos<=24+104*5) all_down();
    
    if (pos>24+104*5 & pos<=24+104*5+104/4) type('x');
    if (pos>24+104*5+104/4) all_down();
    
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
//    case h:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
//      break;
//      break;
//    case i:
//      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
//      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
//      break;
//    case j:
//      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],LOW); digitalWrite(dot[6],LOW);
//      break;
//    case k: 
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
//      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
//      break;
//    case l:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
//      break;
//    case m:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);;
//      break;
//    case n:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
//      break;
//    case o:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
//      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
//      break;
//    case p:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
//      break;
//    case q:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
//      break;
//    case r:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
//      break;
//    case s:
//      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
//      break;
//    case t:
//      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],LOW);
//      break;
//    case u:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
//      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
//      break;
//    case v:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],LOW);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
//      break;
//    case w:
//      digitalWrite(dot[1],LOW); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],HIGH); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],LOW); digitalWrite(dot[6],HIGH);
//    case x:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],LOW); digitalWrite(dot[5],LOW);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
//      break;
//    case y:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],HIGH);
//      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
//      break;
//    case z:
//      digitalWrite(dot[1],HIGH); digitalWrite(dot[4],LOW);
//      digitalWrite(dot[2],LOW); digitalWrite(dot[5],HIGH);
//      digitalWrite(dot[3],HIGH); digitalWrite(dot[6],HIGH);
//      break;
//      
    }
  }
