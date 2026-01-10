%% 
clear all;
close all;
clc

%%
addpath('Function');

%%
%配置文件。
config_file = '../Topic/Topic.xlsx';
%日志文件。
log_file = '../_Example/log.ulg';

%% 
global log;
global variable_detail;
variable_detail = ExcelParse(config_file);
LogCreate();
ParseProcess(log_file);

%%
%清理过程变量
clear config_file
clear log_file
clear variable_detail

%%
%保存结果。
save('log');