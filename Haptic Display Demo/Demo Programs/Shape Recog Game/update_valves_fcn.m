function update_valves_fcn()
global a; 
global pin_array 
global SRCLK_Pin 
global RCLK_Pin 
global SER_Pin 

%updates the value of the solenoid valves to correspond to the pin_array
  writeDigitalPin(a, RCLK_Pin, 0);

  for i = 8:-1:1; 
    writeDigitalPin(a, SRCLK_Pin, 0);
    for j = 1:7
      if (pin_array(j,i) == 1)
      writeDigitalPin(a, SER_Pin(j), 1);
      else
      writeDigitalPin(a, SER_Pin(j), 0);
      end
    end     
    writeDigitalPin(a, SRCLK_Pin, 1);
  end
  writeDigitalPin(a, RCLK_Pin, 1);

end

