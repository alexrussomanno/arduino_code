% Writes the pin_array to the LED output-- Currently writes them 1 by 1 and
% turns off immediately afterwords. This is just copied from Alex's code,
% needs to be improved for matlab
function refreshScreen_fcn()
global col;
global row;
global a;
global pin_array;
%    updates values of the LEDs
  for thisPin = 1:8 
%      makes sure the LEDS are off 
   	writeDigitalPin(a, col(thisPin), 0);   
    writeDigitalPin(a, row(thisPin), 1);
  end

  for x = 1:8
    for y = 1:7 
      if (pin_array(y, x) == 1) 
        writeDigitalPin(a,col(x), 1);
        writeDigitalPin(a,row(y), 0);
        writeDigitalPin(a,col(x), 0);
        writeDigitalPin(a,row(y), 1);
      end
    end
  end
end

      
    
  
