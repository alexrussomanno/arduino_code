% Takes in a case number and writes all the pins high to the variable
% pin_array for that case number

function Pick_Shape_fcn(num)
global pin_array;
global r;
global r2;
switch num
    case 0 % Full Board
        pin_fcn(1,1,1); pin_fcn(1,2,1); pin_fcn(1,3,1); pin_fcn(1,4,1); pin_fcn(1,5,1); pin_fcn(1,6,1); pin_fcn(1,7,1); pin_fcn(1,8,1);
        pin_fcn(2,1,1); pin_fcn(2,2,1); pin_fcn(2,3,1); pin_fcn(2,4,1); pin_fcn(2,5,1); pin_fcn(2,6,1); pin_fcn(2,7,1); pin_fcn(2,8,1);
        pin_fcn(3,1,1); pin_fcn(3,2,1); pin_fcn(3,3,1); pin_fcn(3,4,1); pin_fcn(3,5,1); pin_fcn(3,6,1); pin_fcn(3,7,1); pin_fcn(3,8,1);
        pin_fcn(4,1,1); pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1); pin_fcn(4,7,1); pin_fcn(4,8,1);
        pin_fcn(5,1,1); pin_fcn(5,2,1); pin_fcn(5,3,1); pin_fcn(5,4,1); pin_fcn(5,5,1); pin_fcn(5,6,1); pin_fcn(5,7,1); pin_fcn(5,8,1);
        pin_fcn(6,1,1); pin_fcn(6,2,1); pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1); pin_fcn(6,7,1); pin_fcn(6,8,1);
        pin_fcn(7,1,1); pin_fcn(7,2,1); pin_fcn(7,3,1); pin_fcn(7,4,1); pin_fcn(7,5,1); pin_fcn(7,6,1); pin_fcn(7,7,1); pin_fcn(7,8,1);
    case 1 %Solid Right Triangle
        pin_fcn(3, 4, 1);  
        pin_fcn(4, 4, 1); pin_fcn(4 ,5, 1); 
        pin_fcn(5 ,4 ,1); pin_fcn(5, 5, 1); pin_fcn(5 ,6, 1);
%         disp('Case 1');
    case 2 %Hollow Right Triangle
        pin_fcn(2,3,1); 
        pin_fcn(3,3,1); pin_fcn(3,4,1);
        pin_fcn(4,3,1); pin_fcn(4,5,1);
        pin_fcn(5,3,1); pin_fcn(5,6,1);
        pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1); pin_fcn(6,7,1);
%         disp('Case 2');
    case 3 %Solid Rectangle
        pin_fcn(2,2,1); pin_fcn(2,3,1); pin_fcn(2,4,1); pin_fcn(2,5,1); pin_fcn(2,6,1); pin_fcn(2,7,1);
        pin_fcn(3,2,1); pin_fcn(3,3,1); pin_fcn(3,4,1); pin_fcn(3,5,1); pin_fcn(3,6,1); pin_fcn(3,7,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1); pin_fcn(4,7,1);
        pin_fcn(5,2,1); pin_fcn(5,3,1); pin_fcn(5,4,1); pin_fcn(5,5,1); pin_fcn(5,6,1); pin_fcn(5,7,1);
        pin_fcn(6,2,1); pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1); pin_fcn(6,7,1);
%         disp('Case 3');
    case 4 %Hollow Rectangle
        pin_fcn(2,2,1); pin_fcn(2,3,1); pin_fcn(2,4,1); pin_fcn(2,5,1); pin_fcn(2,6,1); pin_fcn(2,7,1);
        pin_fcn(3,2,1); pin_fcn(3,7,1);
        pin_fcn(4,2,1); pin_fcn(4,7,1);
        pin_fcn(5,2,1); pin_fcn(5,7,1);
        pin_fcn(6,2,1); pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1); pin_fcn(6,7,1);
%         disp('Case 4');
    case 5 %Solid Square
        pin_fcn(3,3,1); pin_fcn(3,4,1); pin_fcn(3,5,1); pin_fcn(3,6,1);
        pin_fcn(4,3,1); pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1);
        pin_fcn(5,3,1); pin_fcn(5,4,1); pin_fcn(5,5,1); pin_fcn(5,6,1);
        pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1);
%         disp('Case 5');
    case 6 %Hollow Square 
        pin_fcn(3,3,1); pin_fcn(3,4,1); pin_fcn(3,5,1); pin_fcn(3,6,1);
        pin_fcn(4,3,1); pin_fcn(4,6,1);
        pin_fcn(5,3,1); pin_fcn(5,6,1);
        pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1);  
%         disp('Case 6');
    case 7 %Solid Octogon
        pin_fcn(2,4,1); pin_fcn(2,5,1);
        pin_fcn(3,3,1); pin_fcn(3,4,1); pin_fcn(3,5,1); pin_fcn(3,6,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1); pin_fcn(4,7,1);
        pin_fcn(5,2,1); pin_fcn(5,3,1); pin_fcn(5,4,1); pin_fcn(5,5,1); pin_fcn(5,6,1); pin_fcn(5,7,1);
        pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1);
        pin_fcn(7,4,1); pin_fcn(7,5,1);
%         disp('Case 7');
    case 8 %Hollow Octogon   
        pin_fcn(2,4,1); pin_fcn(2,5,1);
        pin_fcn(3,3,1); pin_fcn(3,6,1);
        pin_fcn(4,2,1); pin_fcn(4,7,1);
        pin_fcn(5,2,1); pin_fcn(5,7,1);
        pin_fcn(6,3,1); pin_fcn(6,6,1);
        pin_fcn(7,4,1); pin_fcn(7,5,1);
%         disp('Case 8');
    case 9 %Solid Sideways Triangle
        pin_fcn(1,4,1);
        pin_fcn(2,4,1); pin_fcn(2,5,1); 
        pin_fcn(3,4,1); pin_fcn(3,5,1); pin_fcn(3,6,1);
        pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1); pin_fcn(4,7,1);
        pin_fcn(5,4,1); pin_fcn(5,5,1); pin_fcn(5,6,1);
        pin_fcn(6,4,1); pin_fcn(6,5,1);
        pin_fcn(7,4,1);
%         disp('Case 9');
    case 10 %Hollow Sideways Triangle
        pin_fcn(1,4,1);
        pin_fcn(2,4,1); pin_fcn(2,5,1); 
        pin_fcn(3,4,1); pin_fcn(3,6,1);
        pin_fcn(4,4,1); pin_fcn(4,7,1);
        pin_fcn(5,4,1); pin_fcn(5,6,1);
        pin_fcn(6,4,1); pin_fcn(6,5,1);
        pin_fcn(7,4,1);
%         disp('Case 10');
    case 11 %Solid Rhombus
        pin_fcn(2,4,1);
        pin_fcn(3,3,1); pin_fcn(3,4,1); pin_fcn(3,5,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1);
        pin_fcn(5,3,1); pin_fcn(5,4,1); pin_fcn(5,5,1);
        pin_fcn(6,4,1);
%         disp('Case 11');
    case 12 %Hollow Rhombus
        pin_fcn(2,4,1);
        pin_fcn(3,3,1); pin_fcn(3,5,1);
        pin_fcn(4,2,1); pin_fcn(4,6,1);
        pin_fcn(5,3,1); pin_fcn(5,5,1);
        pin_fcn(6,4,1);
%         disp('Case 12');
    case 13 %Left Arrow
        pin_fcn(2,4,1);
        pin_fcn(3,3,1); pin_fcn(3,4,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1); pin_fcn(4,7,1);
        pin_fcn(5,3,1); pin_fcn(5,4,1);
        pin_fcn(6,4,1);
%         disp('Case 13');
    case 14 %Right Arrow
        pin_fcn(2,5,1);
        pin_fcn(3,5,1); pin_fcn(3,6,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1); pin_fcn(4,7,1);
        pin_fcn(5,5,1); pin_fcn(5,6,1);
        pin_fcn(6,5,1);
%         disp('Case 14');
    case 15 %Up Arrow
        pin_fcn(2,4,1);
        pin_fcn(3,3,1); pin_fcn(3,4,1); pin_fcn(3,5,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1);
        pin_fcn(5,4,1);
        pin_fcn(6,4,1);
        pin_fcn(7,4,1);
%         disp('Case 15');
    case 16 %Down Arrow
        pin_fcn(1,4,1);
        pin_fcn(2,4,1);
        pin_fcn(3,4,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1); pin_fcn(4,5,1); pin_fcn(4,6,1);
        pin_fcn(5,3,1); pin_fcn(5,4,1); pin_fcn(5,5,1);
        pin_fcn(6,4,1);
%         disp('Case 16');
    case 17 %Diag Up Left Arrow
        pin_fcn(2,2,1); pin_fcn(2,3,1); pin_fcn(2,4,1); pin_fcn(2,5,1);
        pin_fcn(3,2,1); pin_fcn(3,3,1); pin_fcn(3,4,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1);
        pin_fcn(5,2,1); pin_fcn(5,5,1);
        pin_fcn(6,6,1);
%         disp('Case 17');
    case 18 %Diag Up Right Arrow
        pin_fcn(2,4,1); pin_fcn(2,5,1); pin_fcn(2,6,1); pin_fcn(2,7,1);
        pin_fcn(3,5,1); pin_fcn(3,6,1); pin_fcn(3,7,1);
        pin_fcn(4,5,1); pin_fcn(4,6,1); pin_fcn(4,7,1);
        pin_fcn(5,4,1); pin_fcn(5,7,1);
        pin_fcn(6,3,1);
%         disp('Case 18');
    case 19 %Diag Down Left Arrow
        pin_fcn(2,6,1);
        pin_fcn(3,2,1); pin_fcn(3,5,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,4,1);
        pin_fcn(5,2,1); pin_fcn(5,3,1); pin_fcn(5,4,1);
        pin_fcn(6,2,1); pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1);
%         disp('Case 19');
    case 20 %Diag Down Right Arrow
        pin_fcn(2,3,1);
        pin_fcn(3,4,1); pin_fcn(3,7,1);
        pin_fcn(4,5,1); pin_fcn(4,6,1); pin_fcn(4,7,1);
        pin_fcn(5,5,1); pin_fcn(5,6,1); pin_fcn(5,7,1);
        pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1); pin_fcn(6,7,1);
%         disp('Case 20');
    case 21 %Five Dice
        pin_fcn(2,2,1); pin_fcn(2,3,1); pin_fcn(2,6,1); pin_fcn(2,7,1);
        pin_fcn(3,2,1); pin_fcn(3,3,1); pin_fcn(3,6,1); pin_fcn(3,7,1);
        pin_fcn(4,4,1); pin_fcn(4,5,1);
        pin_fcn(5,4,1); pin_fcn(5,5,1);
        pin_fcn(6,2,1); pin_fcn(6,3,1); pin_fcn(6,6,1); pin_fcn(6,7,1);
        pin_fcn(7,2,1); pin_fcn(7,3,1); pin_fcn(7,6,1); pin_fcn(7,7,1);
%         disp('Case 21');
    case 22 %Inverse Five Dice
        pin_fcn(2,4,1); pin_fcn(2,5,1);
        pin_fcn(3,4,1); pin_fcn(3,5,1);
        pin_fcn(4,2,1); pin_fcn(4,3,1); pin_fcn(4,6,1); pin_fcn(4,7,1);
        pin_fcn(5,2,1); pin_fcn(5,3,1); pin_fcn(5,6,1); pin_fcn(5,7,1);
        pin_fcn(6,4,1); pin_fcn(6,5,1);
        pin_fcn(7,4,1); pin_fcn(7,5,1); 
%         disp('Case 22');
    case 23 %L Bottom Left
        pin_fcn(2,2,1);
        pin_fcn(3,2,1);
        pin_fcn(4,2,1);
        pin_fcn(5,2,1);
        pin_fcn(6,2,1); pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1);
%         disp('Case 23');
    case 24 %L Bottom Right
        pin_fcn(2,7,1);
        pin_fcn(3,7,1);
        pin_fcn(4,7,1);
        pin_fcn(5,7,1);
        pin_fcn(6,3,1); pin_fcn(6,4,1); pin_fcn(6,5,1); pin_fcn(6,6,1); pin_fcn(6,7,1);
%         disp('Case 24');
    case 25 %L Top Left
        pin_fcn(2,2,1); pin_fcn(2,3,1); pin_fcn(2,4,1); pin_fcn(2,5,1); pin_fcn(2,6,1);
        pin_fcn(3,2,1); 
        pin_fcn(4,2,1);
        pin_fcn(5,2,1);
        pin_fcn(6,2,1);
%         disp('Case 25');
    case 26 %L Top Right
        pin_fcn(2,3,1); pin_fcn(2,4,1); pin_fcn(2,5,1); pin_fcn(2,6,1); pin_fcn(2,7,1);
        pin_fcn(3,7,1);
        pin_fcn(4,7,1);
        pin_fcn(5,7,1);
        pin_fcn(6,7,1);
%         disp('Case 26');
end