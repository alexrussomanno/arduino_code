% WRITE PIN
% Write the pin to variable called pin_array
% pin_array is set to all zeros so onlly have to write high but have it
% programed so you could write low if you wanted to

function pin_fcn(y, x, s)
global pin_array;
 
    if (s == 1)       %Write it on
      pin_array(y,x) = 1;
%     disp('wrote 1');
    end
    if (s == 0)       % Write it off
    pin_array(y,x) = 0;
%     disp('wrote 0');
    end
end