/* 
Date: 9/3/14
This file uses the linear encoder and the stepper motor. It includes the following functions:
  1) step: Steps a certain number of steps in a certain direction
  2) step_to: Steps to a particular encoder position

*/


#define CH_A 19            // Encoder Channel A - This pin can call an ISR on Arduino Mega
#define CH_B 18            // Encoder Channel B - This pin can call an ISR on Arduino Mega
#define motor_pin_1 8
#define motor_pin_2 9

volatile int encPos=0;
int step_number = 0;      // which step the motor is on
int speed = 0;        // the motor speed, in revolutions per minute
int direction = 0;      // motor direction
unsigned long last_step_time = 0;    // time stamp in ms of the last step taken
int number_of_steps = 200;    // total number of steps for this motor
int pin_count = 2;
int step_delay = 0;  

         

void setup() {
  pinMode(CH_A, INPUT); //Encoder channel A
  pinMode(CH_B, INPUT); //Encoder channel B
  attachInterrupt(4, readEncoderA, CHANGE); // attach interrupt to encoder channel A
  attachInterrupt(5, readEncoderB, CHANGE); // attach interrupt to encoder channel B
  
  pinMode(motor_pin_1, OUTPUT);
  pinMode(motor_pin_2, OUTPUT);
  // set the speed at 60 rpm:
  set_speed(120);
  Serial.begin(9600);
}

void loop() {
//  ste
//  
//  Serial.println(encPos);
//  step_to_pos(4000);
//  Serial.println(encPos);
//  delay(10000);
//  Serial.println(encPos);
//  step(200);
//  delay(500);
//  step(-200);
//  delay(500);
  
}

/* 
MOTOR STUFF
*/
void set_speed(long whatSpeed)
 // Sets the speed in revs per minute
{
  step_delay = 60L * 1000L / number_of_steps / whatSpeed;
}


void step_to(int new_encPos)
/*
  Moves the motor to a specific encoder position
 */
{   
  // determine direction based on whether steps_to_mode is + or -:
  if (new_encPos > encPos) {direction = 1;}
  if (new_encPos < encPos) {direction = 0;}
    
    
  while(encPos != new_encPos) {
  // move only if the appropriate delay has passed:
    if (millis() - last_step_time >= step_delay) {
        // get the timeStamp of when you stepped:
        last_step_time = millis();
        // increment or decrement the step number,
        // depending on direction:
        if (direction == 1) {
          step_number++;
          if (step_number == number_of_steps) {
            step_number = 0;
          }
        } 
        else { 
          if (step_number == 0) {
            step_number = number_of_steps;
          }
          step_number--;
        }
        // step the motor to step number 0, 1, 2, or 3:
        stepMotor(step_number % 4);
      }
  }
}

void step(int steps_to_move)
/*
  Moves the motor steps_to_move steps.  If the number is negative, 
   the motor moves in the reverse direction.
 */
{  
  int steps_left = abs(steps_to_move);  // how many steps to take
  
  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) {direction = 1;}
  if (steps_to_move < 0) {direction = 0;}
    
    
  // decrement the number of steps, moving one step each time:
  while(steps_left > 0) {
  // move only if the appropriate delay has passed:
  if (millis() - last_step_time >= step_delay) {
      // get the timeStamp of when you stepped:
      last_step_time = millis();
      // increment or decrement the step number,
      // depending on direction:
      if (direction == 1) {
        step_number++;
        if (step_number == number_of_steps) {
          step_number = 0;
        }
      } 
      else { 
        if (step_number == 0) {
          step_number = number_of_steps;
        }
        step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, 2, or 3:
      stepMotor(step_number % 4);
    }
  }
}

void stepMotor(int thisStep)
// Moves the motor forward or backwards
{
  if (pin_count == 2) {
    switch (thisStep) {
      case 0: /* 01 */
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, HIGH);
      break;
      case 1: /* 11 */
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, HIGH);
      break;
      case 2: /* 10 */
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, LOW);
      break;
      case 3: /* 00 */
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, LOW);
      break;
    } 
  }
}

/* 
ENCODER STUFF
*/
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
