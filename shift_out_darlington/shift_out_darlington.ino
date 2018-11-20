//Pin connected to ST_CP of 74HC595 or RCLK
int latchPin = 5;
//Pin connected to SH_CP of 74HC595 or SRCLK
int clockPin = 4;
////Pin connected to DS of 74HC595  or SER
int dataPin = 3;



void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(500);
  }
}

/*
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
     uint8_t i;

     for (i = 0; i < 8; i++)  {
           if (bitOrder == LSBFIRST)
                 digitalWrite(dataPin, !!(val & (1 << i)));
           else      
                 digitalWrite(dataPin, !!(val & (1 << (7 - i))));
                 
           digitalWrite(clockPin, HIGH);
           digitalWrite(clockPin, LOW);            
     }
}
*/
