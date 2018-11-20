  int SERbutton = 1;
  int RCLKbutton = 2;
  int SRCLKbutton = 3;
  int SER = 8;
  int RCLK = 9;
  int SRCLK = 10;

  void setup() {
    pinMode(SERbutton, INPUT);
    pinMode(RCLKbutton, INPUT);
    pinMode(SRCLKbutton, INPUT);
    
    pinMode(SER, INPUT);
    pinMode(RCLK, INPUT);
    pinMode(SRCLK, INPUT);
  }
  
   void loop() {
     if (digitalRead(SERbutton)==HIGH){
       digitalWrite(SER,HIGH);
     }
     else{digitalWrite(SER,LOW);}
    
     if (digitalRead(RCLKbutton)==HIGH){
       digitalWrite(RCLK,HIGH);
     }
     else{digitalWrite(RCLK,LOW);}
     
     if (digitalRead(SRCLKbutton)==HIGH){
       digitalWrite(SRCLK,HIGH);
     }
     else{digitalWrite(SRCLK,LOW);}
    
    
   }
