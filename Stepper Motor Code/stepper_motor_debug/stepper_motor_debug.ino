/* 
9/3/14
This is the raw code used to drive a stepper motor. It was taken from the Stepper.h library.
*/
 
 #define motor_pin_1 8
 #define motor_pin_2 9
 
  int step_number = 0;      // which step the motor is on
  int speed = 0;        // the motor speed, in revolutions per minute
  int direction = 0;      // motor direction
  unsigned long last_step_time = 0;    // time stamp in ms of the last step taken
  int number_of_steps = 200;    // total number of steps for this motor
  int pin_count = 2;
  int step_delay = 0;

  // setup the pins on the microcontroller:
  void setup(){
    pinMode(motor_pin_1, OUTPUT);
    pinMode(motor_pin_2, OUTPUT);
    set_speed(120);
    Serial.begin(9600);
  }
 
 void loop(){
   step_val(200);
   delay(500);
   step_val(-200);
   delay(500);
 }


void set_speed(long whatSpeed) // Sets the speed in revs per minute
{
  step_delay = 60L * 1000L / number_of_steps / whatSpeed;
}

/*
  Moves the motor steps_to_move steps.  If the number is negative, 
   the motor moves in the reverse direction.
 */
void step_val(int steps_to_move)
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

/*
 * Moves the motor forward or backwards.
 */
void stepMotor(int thisStep)
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
