function CodeGenerate_Type(headerFile, variable_detail)
%% 
%逐个变量处理。
for i = 1:variable_detail.Number
    %写入结构体开始。
    fprintf(headerFile, 'typedef struct \n');
    fprintf(headerFile, '{ \n');
    
    %添加时间戳。
    fprintf(headerFile, '  unsigned long long timestamp; \n');
    
    %确定结构体元素数量。
    stringTemp = ['variable_detail.Var' num2str(i)];
    eval(['[elementNumber, ~] = size(' stringTemp ');']);
    %逐个元素产生代码。  
    for j = 1:elementNumber
        %获得每个元素的类型、维数和名称。
        eval(['typeVar = char(' stringTemp '(j, 1));']);
        eval(['dimensionVar = ' stringTemp '{j, 2};']);
        eval(['nameVar = char(' stringTemp '(j, 3));']);
        %声明结构体的一个元素。
        fprintf(headerFile, ['  ' typeVar ' ' nameVar]);
        if dimensionVar > 1
            fprintf(headerFile, ['[' num2str(dimensionVar) ']']);
        end
        fprintf(headerFile, ';\n');
    end
    
    %写入结构体结尾。
    fprintf(headerFile, ['}ULog_' char(variable_detail.Name(i)) '_T; \n']);
    fprintf(headerFile, '\n');
end

end