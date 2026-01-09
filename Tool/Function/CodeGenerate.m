function CodeGenerate(topic_name, variable_detail)

%% 
%产生头文件和源文件的句柄。
headerFile = fopen(['../Topic/' topic_name '.h'], 'w');
sourceFile = fopen(['../Topic/' topic_name '.c'], 'w');

%% 
%输入头文件的编译代码。
fprintf(headerFile, ['#ifndef _' topic_name '_H_\n']);
fprintf(headerFile, ['#define _' topic_name '_H_\n']);
fprintf(headerFile, '\n');
%头文件包含。
fprintf(headerFile, '#include "ulog.h"\n');
fprintf(headerFile, '\n');
%头文件声明外部变量。
fprintf(headerFile, ['extern ULog_Variable_Enter_T ulog_enter_' topic_name ';\n']);
fprintf(headerFile, '\n');
%源文件包含。
fprintf(sourceFile, ['#include "' topic_name '.h"\n\n']);
fprintf(headerFile, '\n');

%%
%产生变量定义。
CodeGenerate_Type(headerFile, variable_detail);

%%
%产生编码函数。
CodeGenerate_Encoder(topic_name, sourceFile, variable_detail);

%%
%产生格式和订阅代码。
CodeGenerate_FormatSubscribe(topic_name, sourceFile, variable_detail);

%% 
%编辑结束部分，并关闭文件。
fprintf(headerFile, '#endif\n');
fclose(headerFile);
fclose(sourceFile);
end