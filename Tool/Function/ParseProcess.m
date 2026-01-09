function ParseProcess(log_file)

%%
global log;
global variable_detail;

%%
file = fopen(log_file);

%略过文件头。
fread(file, 16, 'uint8');

while true
%读取消息流的头。
    messageHeader = uint8(fread(file, 3, 'uint8'));
    if size(messageHeader) == 0
        break;
    end
    
%判断消息类型和长度。
    messageSize = typecast(messageHeader(1:2), 'uint16');
    messageType = messageHeader(3);
    
%读取消息数据。
    messageData = uint8(fread(file, messageSize, 'uint8'));

%只处理数据记录。
    if messageType == uint8(68)
        messageID = typecast(messageData(1:2), 'uint16');
        messageID = messageID + 1;
        VariableProcess(messageID, messageData(3:end));
    end
end

%%
%清除过程数据。
for i = 1:variable_detail.Number
    variableName = ['log.' char(variable_detail.Name(i))];
    fieldName = '''dataTotalNumber''';
    eval([variableName '= rmfield(' variableName ',' fieldName ');']);
end

end