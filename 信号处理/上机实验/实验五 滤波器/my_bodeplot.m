function my_bodeplot(Hw)
%   本函数对传递函数Hw实现可视化，展示不同角频率情况下，传递函数Hw的增益大小
opts=bodeoptions;
opts.PhaseVisible = 'off';
opts.FreqScale = 'linear';
opts.MagUnits = 'abs';
bodeplot(Hw,opts)
grid
end

