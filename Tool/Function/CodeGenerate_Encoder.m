function CodeGenerate_Encoder(topic_name, sourceFile, variable_detail)
%%
maxVariableSize = 0;
fprintf(sourceFile, '__weak static unsigned char default_buffer[];\n\n');
%% 
%声明函数。
for i = 1:variable_detail.Number
    functionName(i) = {['ULog_Encoder_' char(variable_detail.Name(i))]};
    fprintf(sourceFile, ['static unsigned int ' char(functionName(i)) '(void * p_value);\n']);
end
%声明入口初始化函数。
fprintf(sourceFile, ['static void ULog_' topic_name '_Enter_Init();\n']);
fprintf(sourceFile, '\n');

%% 
%创建变量写入口。
%创建变量入口数组。
fprintf(sourceFile, 'ULog_Variable_T ulog_enter_array[] = \n');
fprintf(sourceFile, '{\n');
for i = 1:variable_detail.Number
    fprintf(sourceFile, ['  {"' char(variable_detail.Name(i)) '", ' char(functionName(i)) '},\n']);
end
%结束变量入口数组。
fprintf(sourceFile, '};\n');
fprintf(sourceFile, '\n');

%声明变量。
fprintf(sourceFile, ['ULog_Variable_Enter_T ulog_enter_' topic_name ' = \n']);
fprintf(sourceFile, '{\n');
%给元素附值。
fprintf(sourceFile, ['  ULog_' topic_name '_Enter_Init, 0, 0, default_buffer, ' num2str(variable_detail.Number) ', ulog_enter_array\n']);
%每个变量的名称和写函数。
%结束变量写入口。
fprintf(sourceFile, '};\n');
fprintf(sourceFile, '\n');

%%
%为每个变量生成函数体。
for i = 1:variable_detail.Number
    fprintf(sourceFile, ['static unsigned int ' char(functionName(i)) '(void * p_value)\n']);
    fprintf(sourceFile, '{\n');
    
    %确定结构体元素数量。
    stringTemp = ['variable_detail.Var' num2str(i)];
    eval(['[elementNumber, ~] = size(' stringTemp ');']);
    
    %声明指针变量。
    typeName = ['  ULog_' char(variable_detail.Name(i)) '_T'];
    fprintf(sourceFile, [typeName ' * pVar = (' typeName ' *)p_value;\n']);
    fprintf(sourceFile, '  unsigned char * pData;\n');
    fprintf(sourceFile, '\n');
    
    %消息头的偏移。
    counter = 5;
    
    %拷贝时间戳。
    fprintf(sourceFile, '  pData = (unsigned char *)&(pVar->timestamp);\n');
    fprintf(sourceFile, ['  memcpy(&default_buffer[' num2str(counter) '], pData, 8);\n']);
    fprintf(sourceFile, '\n');
    counter = counter + 8;
    
    %逐个元素产生代码。  
    for j = 1:elementNumber
        %获得每个元素的类型、维数和名称。
        eval(['typeVar = char(' stringTemp '(j, 1));']);
        eval(['dimensionVar = ' stringTemp '{j, 2};']);
        eval(['nameVar = char(' stringTemp '(j, 3));']);
        %将当前指针指向对应元素。
        if dimensionVar > 1
            fprintf(sourceFile, ['  pData = (unsigned char *)(pVar->' nameVar ');\n']);
        else
            fprintf(sourceFile, ['  pData = (unsigned char *)&(pVar->' nameVar ');\n']);
        end
        %确定拷贝长度。
        copySize = dimensionVar * TypeSize(typeVar);
        %拷贝数据。
        fprintf(sourceFile, ['  memcpy(&default_buffer[' num2str(counter) '], pData, ' num2str(copySize) ');\n']);
        fprintf(sourceFile, '\n');
        %更新缓存索引。
        counter = counter + copySize;
    end
    
    %完善消息头。
    %msg_size
    msg_size = typecast(uint16(counter - 3), 'uint8');
    fprintf(sourceFile, ['  default_buffer[0] = ' num2str(msg_size(1)) ';\n']);
    fprintf(sourceFile, ['  default_buffer[1] = ' num2str(msg_size(2)) ';\n']);
    %msg_type 'D'
    fprintf(sourceFile, '  default_buffer[2] = 0x44;\n');
    %msg_id，按照变量在配置文件中存储的顺序，从0开始。
    msg_id = typecast(uint16(i-1), 'uint8');
    fprintf(sourceFile, ['  default_buffer[3] = ' num2str(msg_id(1)) ';\n']);
    fprintf(sourceFile, ['  default_buffer[4] = ' num2str(msg_id(2)) ';\n']);
    
    %确定所有变量中，所需要的最大缓存。
    if maxVariableSize < counter
        maxVariableSize = counter;
    end
    
    %输出返回值。
    fprintf(sourceFile, '\n');
    fprintf(sourceFile, ['  return ' num2str(counter) ';\n']);

    %结束函数。
    fprintf(sourceFile, '}\n');
    fprintf(sourceFile, '\n');
end

%声明缓存。
fprintf(sourceFile, ['static unsigned char default_buffer[' num2str(maxVariableSize) '] = {0};\n']);
fprintf(sourceFile, '\n');

end