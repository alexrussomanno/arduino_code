clc;
clear all;

global a;
a = arduino('/dev/cu.usbmodem1411','uno');
global pin_array;
global row;
global col;
global r;
global r2;
global score;
global num_wrong;
global numtrys;
global total_trys;
global filename;

global SRCLK_Pin 
global RCLK_Pin 
global SER_Pin 
 
filename = 'Test_';
 
num_wrong = 0;
score = 0;
numtrys = 1;
pin_array = [ 0 0 0 0 0 0 0 0
              0 0 0 0 0 0 0 0
              0 0 0 0 0 0 0 0
              0 0 0 0 0 0 0 0
              0 0 0 0 0 0 0 0
              0 0 0 0 0 0 0 0
              0 0 0 0 0 0 0 0 ];
          
 
SER_Pin = [11,10,9,8,7,6,5]; 
SRCLK_Pin = 12; 
RCLK_Pin = 13; 


% PIN NUMBERS set to row(_)
row = [22, 24, 26, 28, 46, 48, 50, 52];
col = [30, 32, 34, 36, 38, 40, 42, 44];

for i=5:13
    configurePin(a,['D' num2str(i)],'DigitalOutput');
end


global all_casenums;
global right_casenum;
global locations;
global their_first_guess;
global correct_first_guess;
global their_second_guess;
global their_third_guess;
global mat_num_wrong;
global mat_score;
global time_per_set;
global base;
global in_a_row;
global elapse; 
global name;
global final_score;
global check;
global top_score_chart;

% top_score_chart = { 'Matt Murdock', 13000;
%                     'Jonn Jonzz', 12000;
%                     'Bruce Wayne', 11000;
%                     'Steve Rogers', 10000;
%                     'Tony Stark', 9000;
%                     'Bruce Banner', 8000;
%                     'Oliver Queen', 7000;
%                     'Barry Allen', 6000;
%                     'Diana Prince', 5000;
%                     'Dr. Harleen Quinzel', 4500; };
                    
load top_score.mat top_score_chart

%If you rerun the program it will write over your old test_# files with the
%new data

for num_games=1:10 %%% Runs 10 games then kicks you out--Can increase this;
    % Resets the game and makes a incremented file for the next game
    reset_game_fcn();
    clear_plots_fcn();              
    clearpins_fcn(); 
    filename = 'Test_';
    filename=[filename,num2str(num_games)];
    disp('NEW GAME!');
    prompt = 'What is your name? ';
    name = input(prompt, 's');
    input('Press enter to begin:');

%     total_time = 0;
%%%%%%%%%%%%% ACTUAL GAME %%%%%%%%%%%%%%%%%%%
    while (num_wrong <= 4) || (score == 11)          %  Three strikes or Score of 10 (actual limits on bottom)

        rand_nums_fcn();                    % Creates random set of five numbers  
                                            % from 1-26 and picks one of
                                            % those 5 to use
                                            
        for i = 1:5                         % Saves all the case numbers
            all_casenums(score+1, i) = r(i);
        end                                         
        locations(score+1) = r2;            % Saves the correct index # to the random set of five cases
                                          
        right_case = r(r2);
        
        
        figure(1);
        for i=1:5
            Pick_Shape_fcn(r(i))        % Updates the pin_array with shape
            Draw_Shape_fcn(i)           % Draws the shape to the subplot
%             if i == r2
%                 refreshScreen_fcn();    % If it is the choosen shape it goes to LED
%                 update_valves_fcn();
%     %             pin_array             % Prints the pin_array to screen
%             end
            clearpins_fcn();            % Clears the pin_array
        end
        
        Pick_Shape_fcn(r(r2));
%         refreshScreen_fcn();    % If it is the choosen shape it goes to LED
        update_valves_fcn();
        clearpins_fcn();
%        disp(r2)                % THIS IS SHOWING THE ANSWER
%         tic
        choice_fcn(r2);                 % Prompts choice
%         toc;                            % Possible to output
%         elaps =toc;
        speed = 30-elapse;    % Subtracts the times 
        H = sprintf('Number of Correct Answers: %d', score);
        disp(H);
        H2 = sprintf('Number of Strikes: %d',num_wrong);
        disp(H2);
        accuracy = score/total_trys;
        clear_plots_fcn();               % Empties the Subplot
        clearpins_fcn(); 
        % The following add information to the savable arrays/matrixes
        % Accounts for if they get all wrong on first set of shapes
        if (num_wrong == 3) && (score == 0)
            right_casenum(1) = right_case;
            mat_num_wrong(1) = num_wrong;
            mat_score(1) = score;
            correct_first_guess(1) = check;
            time_per_set(1) = toc;
%             disp('3 wrong, first try')
        end
        % Accounts for all other cases
        if score > 0
            if num_wrong == 3
                right_casenum(score+1) = right_case;
                mat_num_wrong(score+1) = num_wrong;
                mat_score(score+1) = score;
                correct_first_guess(score+1) = check;
                time_per_set(score+1) = toc;
%             disp(' 3 wrong, writing to spot: ')
%             disp(score+1)
            else            
            right_casenum(score) = right_case;
            mat_num_wrong(score) = num_wrong;
            mat_score(score) = score;
            correct_first_guess(score) = check;
            time_per_set(score) = elapse;
%             disp('writing to spot: ')
%             disp (score)
            end
        end
        % NEEDS ADJUSTING
        
        consistency = accuracy + in_a_row;
        final_score_to_add = (consistency*score*base*speed)/10;
        final_score = final_score+final_score_to_add;
        
        
%         disp('Base: ');
%         disp(base);
%         disp('Accuracy: ');
%         disp(accuracy);
%         disp('In a row: ');
%         disp(in_a_row);
%         disp('Consistency: ');
%         disp(consistency);
%         disp('elapse: ');
%         disp(elapse);
%         disp('Speed: ');
%         disp(speed);
%         disp('Current Score: ');
%         disp(final_score)
        
        % Saves all the data
%         save(filename,'all_casenums', 'right_casenum', 'locations', 'their_first_guess', 'correct_first_guess', 'their_second_guess', 'their_third_guess', 'mat_num_wrong', 'mat_score', 'time_per_set', 'name');

        % Ends the game by either too many strikes or 10 successes
        if num_wrong >= 3
            disp('Three Strikes. GAME OVER')
            final_score = round(final_score);
            H3 = sprintf('Final Score: %d',final_score);
            disp(H3);
            break
        end
        if score == 10
            disp('YOU DID IT! 10 Correct!')
            final_score = round(final_score);
            H4 = sprintf('Final Score: %d',final_score);
            disp(H4);
            break
        end

         % Saves all the data
%         save(filename,'all_casenums', 'right_casenum', 'locations', 'their_first_guess', 'correct_first_guess', 'their_second_guess', 'their_third_guess', 'mat_num_wrong', 'mat_score', 'time_per_set', 'name', 'final_score');
    end
    H5 = sprintf('Number of games: %d',num_games);
    disp(H5);    
     % Saves all the data
    save(filename,'all_casenums', 'right_casenum', 'locations', 'their_first_guess', 'correct_first_guess', 'their_second_guess', 'their_third_guess', 'mat_num_wrong', 'mat_score', 'time_per_set', 'name', 'final_score','top_score_chart');
    Top10_fcn(final_score);
    save('top_score','top_score_chart');
end


