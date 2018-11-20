% Clears the subplot
function clear_plots_fcn()
    for i=1:5
        delete(subplot(3,2,i))
    end
end
