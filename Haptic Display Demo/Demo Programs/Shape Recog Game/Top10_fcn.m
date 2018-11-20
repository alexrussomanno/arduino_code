function Top10_fcn(score_in)

global top_score_chart;
global name;
times = 1;
% scorestring = num2str(score_in);
for scorerow = 1:10
    if (score_in > top_score_chart{scorerow,2}) && (times == 1)
        for(n = 9:-1:scorerow)
            top_score_chart{n+1,2} = top_score_chart{n,2};
            top_score_chart{n+1,1} = top_score_chart{n,1};
        end
        top_score_chart{scorerow,2} = score_in;
        top_score_chart{scorerow,1} = name;
        times = 2;
    end
end
 f = figure(2);
 cnames = {'Name', 'Score'};
 uitable(f,'Data', top_score_chart, 'ColumnName', cnames); %'Title', 'HIGH SCORES',
 
%  disp('TOP TEN: ');
%  disp(top_score_chart);
end