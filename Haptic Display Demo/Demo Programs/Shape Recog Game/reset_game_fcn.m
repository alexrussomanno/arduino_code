% Resets all the variables/saveables of the game to starting points
% Saveables are reset to an appropriately sized array of zeros
function reset_game_fcn()
global num_wrong;
global score;
global numtrys;

global all_casenums;
global right_casenum;
global locations;
global thier_first_guess;
global correct_first_guess;
global thier_second_guess;
global thier_third_guess;
global mat_num_wrong;
global mat_score;
global time_per_set; 
global final_score;
global in_a_row;
global total_trys;

all_casenums = zeros(10,5);
right_casenum = zeros(1,10);
locations = zeros(1,10);
thier_first_guess = zeros(1,10);
correct_first_guess = zeros(1,10);
thier_second_guess = zeros(1,10);
thier_third_guess = zeros(1,10);
mat_num_wrong = zeros(1,10);
mat_score = zeros(1,10);
time_per_set = zeros(1,10);
final_score = 0;
in_a_row = 0;
total_trys = 0;

num_wrong = 0;
score = 0;
numtrys = 1;
end