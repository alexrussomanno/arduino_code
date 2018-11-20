int gauge[]={10, 11, 12, 13, 14, 15};

void setup(){
  Serial.begin(57600);
}

void loop(){
  for (int i = 0; i <6; i++){
    Serial.print(analogRead(gauge[i]),DEC); Serial.print(" ");
  }
  Serial.println();
}
