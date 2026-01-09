%% 
close all;
clear all;
clc;

%% 
N = 100;
n = 1:(N-1);
sineData_1 = sin(2*pi*n/N*1);
sineData_2 = sin(2*pi*n/N*2);
sineData_3 = sin(2*pi*n/N*3);
sineData_4 = sin(2*pi*n/N*4);
%% 
file = fopen('sine_data.h', 'w');

fprintf(file, 'const float sine_data_1[] = {');
for i = n
    fprintf(file, [num2str(sineData_1(i)) ',']);
end
fprintf(file, '};\n');

fprintf(file, 'const float sine_data_2[] = {');
for i = n
    fprintf(file, [num2str(sineData_2(i)) ',']);
end
fprintf(file, '};\n');

fprintf(file, 'const float sine_data_3[] = {');
for i = n
    fprintf(file, [num2str(sineData_3(i)) ',']);
end
fprintf(file, '};\n');

fprintf(file, 'const float sine_data_4[] = {');
for i = n
    fprintf(file, [num2str(sineData_4(i)) ',']);
end
fprintf(file, '};\n');

fclose(file);

