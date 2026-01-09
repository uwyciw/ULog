function VariableProcess(id, payload_data)
%% 
global log;
global variable_detail;

%%
%获得相应标识的数据域信息
field_detail = getfield(variable_detail, ['Var' num2str(id)]);

%% 
%数据域数目
[fieldNumber, ~] = size(field_detail);

%% 
%解析数据
%己使用的负载字节计数值，跳过时间戳。
counter = 9;
for i = 1:fieldNumber
    %根据数据类型确定数据域的字节长度
    byteSize  = TypeSize(char(field_detail(i, 1))) * cell2mat(field_detail(i, 2));
    
    %从数据中解析出变量的值
    value = typecast(uint8(payload_data(counter:counter+byteSize-1)), char(TypeChange(char(field_detail(i, 1)))));
    counter = counter + byteSize;
    
    %将变量值更新到日志变量中
    %结构体字段
    structField = ['log.' char(variable_detail.Name(id)) '.' char(field_detail(i, 3))];
    %更新计数
    updateCounter = ['log.' char(variable_detail.Name(id)) '.dataTotalNumber'];
    
    %确定元素的维数。
    [dimensionNumber, ~] = size(value);
    
    %为各维赋值。
    for j = 1:dimensionNumber
        eval([structField '(' updateCounter '+1, ' num2str(j) ') = value( ' num2str(j) ');']);
    end
end

%更新时间戳。
value = typecast(uint8(payload_data(1:8)), 'uint64');
structField = ['log.' char(variable_detail.Name(id)) '.timestamp'];
eval([structField '(' updateCounter '+1, :) = value;']);

%% 
%更新计数加一
    eval([updateCounter '=' updateCounter '+ 1;']);
    
end