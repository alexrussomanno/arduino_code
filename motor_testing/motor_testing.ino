int M1 = 3;           // the pin that the Motor1 is attached to
int D1 = 2;
int Cmd = 0;    

// the setup routine runs once when you press reset:
void setup()  { 
  
  Serial.begin(9600);
  // declare pin 9 to be an output:
  pinMode(M1, OUTPUT);
  pinMode(D1, OUTPUT);
 
} 

// the loop routine runs over and over again forever:
void loop()  { 
  
  Cmd = 100;
  analogWrite(M1, Cmd);  
  digitalWrite(D1,HIGH);  
  delay(1000);
  digitalWrite(D1,LOW);
  delay(1000); // pauses the program by a set number of milliseconds                           
}

