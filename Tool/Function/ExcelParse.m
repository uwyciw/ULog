function variable_detail = ExcelParse(excel_file)

%%
%获得配置文件中，待解析变量的名称和数目
[~, variable_detail.Name, ~] = xlsfinfo(excel_file);
[~, variable_detail.Number] = size(variable_detail.Name);

%%
%获得每一个表的信息
for i = 1:variable_detail.Number
    [~, ~, structDetail] = xlsread(excel_file, i);
    variable_detail = setfield(variable_detail, ['Var' num2str(i)], structDetail);
end

end