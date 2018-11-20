% CHOICE SELECTION/DISPLAY-- Take thier inputs and keeps track of them to
% be saved for late (accounts for if it was thier 1st, 2nd or 3rd try
function choice_fcn(sol)
global score
global num_wrong
global numtrys 
global total_trys
numtrys=1;
global base;
global in_a_row;
global elapse; 
global their_first_guess;
global their_second_guess;
global their_third_guess;
global check;
count = 1;
tic;
clc; %Add this back in to erase the command window between each shapeset
n = input('Which Shape Matches: ');

    base = 10; 
    check = 1; 
    their_first_guess(score+1)= n;
        while (n > 5) || (n<1)
        n = input('Please chooose a viable option: ');
        numtrys = numtrys+1;
        end
    if n~= sol
        in_a_row = 0;
        num_wrong = num_wrong +1;
        numtrys = numtrys +1;
%         disp('1st option num_wrong: '); disp(num_wrong);
    end
       if num_wrong == 3
          check = 0;
          base = 0;
%                 disp('Happened Shallower')
%                 disp('num_wrong: '); disp(num_wrong);
          return % This causes a problem if they get three strikes on first set
                 % it ends the program without saving the data or
                 % displaying the end game information
       end

    while n ~= sol 
            check = 0;
            m = input('Incorrect. Try again: ');
            if count == 1
                their_second_guess(score+1) = m;
                base = 5;
            end
            if count == 2
                their_third_guess(score+1) = m;
                base = 3;
            end
            while (m > 5) || (m<1)
            m = input('Please chooose a viable option: ');
            end
                if m ~= sol
                 numtrys=numtrys+1;
              	 num_wrong = num_wrong+1;
%                  disp('2nd option num_wrong: '); disp(num_wrong);
                end
            if num_wrong == 3
                base =0;
%                 disp('Happened Deeper')
%                 disp('num_wrong: '); disp(num_wrong);
                return % Same problem as above return statement
            end
            n = m;
            count = count +1;
    end
disp('Correct!');
H7 = sprintf('Number of Attempts: %d', numtrys);
disp(H7);

elapse = toc;
score=score+1;
in_a_row = in_a_row + 1;
total_trys = total_trys+numtrys;
end