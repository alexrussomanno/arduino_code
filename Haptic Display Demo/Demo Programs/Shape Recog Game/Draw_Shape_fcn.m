% Draws representative orange circles to a location on a subplot. Takes in
% location on subplot as input. Bases orange circle locations on variable
% pin_array

function Draw_Shape_fcn(num)

global pin_array

subplot(2,3,num)
axis('equal');
for j = 1:7
    for i = 1:8
        if pin_array(j,i) == 1
            pos = [i 8-j .5 .5];
            rectangle('Position', pos, 'Curvature', [1 1], 'FaceColor', [1 .5 0], 'EdgeColor', 'k' )
            axis([.5 9 .5 8])
            set(gca,'XtickLabel',[],'YtickLabel',[]);
            xlabel(num);
%             set(gca, 'axes','Visible','off')
%             set(gca,'visible','off')
        end    
    end
end
      