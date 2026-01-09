%% 
clear all;
close all;
clc

%%
addpath('Function');

%% 
topic_name = 'Topic';
config_file = '../Topic/Topic.xlsx';

%% 
variable_detail = ExcelParse(config_file);
CodeGenerate(topic_name, variable_detail);
