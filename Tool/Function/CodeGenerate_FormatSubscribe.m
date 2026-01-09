function CodeGenerate_FormatSubscribe(topic_name, sourceFile, variable_detail)

%% 
%格式及订阅的总字节数。
counter = 0;

%% 
%入口初始化函数开始。
fprintf(sourceFile, ['static void ULog_' topic_name '_Enter_Init()\n']);
fprintf(sourceFile, '{\n');

%%
%声明格式变量。
fprintf(sourceFile, '  ULOG_MESSAGE_FORMAT_T format[] = \n');
fprintf(sourceFile, '  {\n');

%逐个变量的初始化。
for i = 1:variable_detail.Number

    %获得元素的个数。
    stringTemp = ['variable_detail.Var' num2str(i)];
    eval(['[elementNumber, ~] = size(' stringTemp ');']);

    %变量名及时间戳域。
    formatString = [char(variable_detail.Name(i)) ':uint64_t timestamp;'];
    %逐个元素初始化。
    for j = 1:elementNumber

        %获得每个元素的类型、维数和名称.
        eval(['typeVar = char(' stringTemp '(j, 1));']);
        eval(['dimensionVar = ' stringTemp '{j, 2};']);
        eval(['nameVar = char(' stringTemp '(j, 3));']);

        if dimensionVar > 1
            formatString = [formatString typeVar '[' num2str(dimensionVar) '] ' nameVar ';'];
        else
            formatString = [formatString typeVar ' ' nameVar ';'];
        end
    end

    %初始化变量。
    [~, formatSize] = size(formatString);
    formatSize = formatSize + 1;
    counter = counter + formatSize + 3;
    fprintf(sourceFile, ['    {' num2str(uint16(formatSize)) ', 0x46, "']);

    %初始化完成一个变量。
    fprintf(sourceFile, [formatString '"},\n']);

end

%格式变量结束。
fprintf(sourceFile, '  };\n');
fprintf(sourceFile, '\n');

%%
%声明订阅变量。
fprintf(sourceFile, '  ULOG_MESSAGE_SUBSCRIBE_T subscribe[] = \n');
fprintf(sourceFile, '  {\n');

%逐个变量的初始化。
for i = 1:variable_detail.Number
    [~, nameLength] = size(char(variable_detail.Name(i)));
    nameLength = nameLength + 1;
    counter = counter + nameLength + 3 + 3;
    fprintf(sourceFile, ['    {' num2str(uint16(nameLength+3)) ', 0x41, 0, ' num2str(i-1) ', "' char(variable_detail.Name(i)) '"},\n']);
end

%订阅变量结束。
fprintf(sourceFile, '  };\n');
fprintf(sourceFile, '\n');

%%
%声明日志头部缓存。
fprintf(sourceFile, ['  static unsigned char ulog_header_buffer[' num2str(counter) '] = {0};\n']);
fprintf(sourceFile, '  int counter = 0;\n');
fprintf(sourceFile, '\n');

%将格式变量拷贝至缓存。
fprintf(sourceFile, ['  for(int i = 0; i < ' num2str(variable_detail.Number) '; i++)\n']);
fprintf(sourceFile, '  {\n');
fprintf(sourceFile, '    memcpy(&ulog_header_buffer[counter], &format[i], 3);\n');
fprintf(sourceFile, '    counter = counter + 3;\n');
fprintf(sourceFile, '    memcpy(&ulog_header_buffer[counter], format[i].format, format[i].msgSize);\n');
fprintf(sourceFile, '    counter = counter + format[i].msgSize;\n');
fprintf(sourceFile, '  }\n');
fprintf(sourceFile, '\n');

%%
%将订阅变量拷贝至缓存。
fprintf(sourceFile, ['  for(int i = 0; i < ' num2str(variable_detail.Number) '; i++)\n']);
fprintf(sourceFile, '  {\n');
fprintf(sourceFile, '    memcpy(&ulog_header_buffer[counter], &subscribe[i], 6);\n');
fprintf(sourceFile, '    counter = counter + 6;\n');
fprintf(sourceFile, '    memcpy(&ulog_header_buffer[counter], subscribe[i].msgName, subscribe[i].msgSize-3);\n');
fprintf(sourceFile, '    counter = counter + subscribe[i].msgSize - 3;\n');
fprintf(sourceFile, '  }\n');
fprintf(sourceFile, '\n');

%%
%更新入口。
fprintf(sourceFile, ['  ulog_enter_' topic_name '.pHeader = ulog_header_buffer;\n']);
fprintf(sourceFile, ['  ulog_enter_' topic_name '.headerSize = ' num2str(counter) ';\n']);

%%
%入口初始化函数结束。
fprintf(sourceFile, '}\n');

end