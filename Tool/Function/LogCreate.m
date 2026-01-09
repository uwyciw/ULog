function LogCreate()

%%
global log;
global variable_detail;

%% 
%待解析日志的变量数目
variableNumber = getfield(variable_detail, 'Number');
 
%% 
%创建日志变量
for i = 1:variableNumber
    eval(['log.' char(variable_detail.Name(i)) '.dataTotalNumber = 0;']);
end

end