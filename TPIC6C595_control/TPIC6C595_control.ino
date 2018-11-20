
// For Arduino UNO
int SER_Pin = 3;  // data
int SRCLK_Pin = 4; // clock
int RCLK_Pin = 5;  // latch

/*        TPIC6C595      
 *           ___
 *      5V -| U |- GND
 *  SER_IN -|   |- GND
 *       0 -|   |- 7
 *       1 -|   |- 6
 *       2 -|   |- 5
 *       3 -|   |- 4
 *      5V -|   |- RCLK
 *     GND -|   |- SER_OUT (to next SER_IN)
 *           ```
 */


// Define number of registers and an array to hold boolean values for each register value
#define num_registers 32
boolean register_value[num_registers];


//// ************************************************ ////

void setup(){
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  
  Serial.begin(9600);
  
  set_all_registers(LOW);
  update_register_values();
}               

void loop(){

// Example code that alternates between setting select_register HIGH and LOW 
// every time "ENTER" is pressed in the Serial port

  int select_register=31;
  while (Serial.read() != 10);
  if(register_value[select_register]==HIGH) register_value[select_register]=LOW;
  else register_value[select_register]=HIGH;  
  
  Serial.println(register_value[select_register]);
    
  update_register_values();
}

// Updates the state of the power shift registers to correspond to the boolean array register_value
void  update_register_values(){
  digitalWrite(RCLK_Pin, LOW);

  for(int i = num_registers - 1; i >=  0; i--){

    int val = register_value[i];
    digitalWrite(SER_Pin, val);
 
    digitalWrite(SRCLK_Pin, HIGH);
    digitalWrite(SRCLK_Pin, LOW);
  }
  digitalWrite(RCLK_Pin, HIGH);

}

// Sets all registers HIGH or LOW
void set_all_registers(boolean state){
  for(int i = 0; i < num_registers; i++){
      register_value[i] = state;
  }
} 
