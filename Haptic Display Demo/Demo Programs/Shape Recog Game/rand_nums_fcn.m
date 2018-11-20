% Generates 5 random case numbers and an index to pick which of those five
% cases to use. Also ensures that no case numbers are repeated
function [r r2] = rand_nums_fcn()
% GENERATE RANDOM CASE NUMBERS OUT OF 26
global r;
global r2; 

r = randi([1 26],1,5);

%%%%%%%%%%% CHECKS FOR NO REPEATED NUMBER IN SET OF FIVE %%%%%%%%%%%
for spot1 = 1:4
    for spot2 = (spot1+1):5
        while(r(spot1) == r(spot2))
            r(spot2) = randi([1 26],1);
%             disp('New Num at spot')
%             disp(spot2)
%             r
        end
    end
end
for back1 = 5:-1:2
    for back2 = back1-1:-1:1
        while(r(back1) == r(back2))
            r(back2) = randi([1 26],1);
%             disp('Redid Num at spot')
%             disp(back2)
%             r
        end
    end
end
% GENERATE RANODOM LOCATION OUT OF 5
r2 = randi([1 5],1);
end