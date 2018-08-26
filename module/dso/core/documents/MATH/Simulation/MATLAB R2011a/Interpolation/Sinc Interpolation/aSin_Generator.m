clear;
clc;
TRIG_90DEG = 1024;
TRIG_DIV_NUM = 32;
angle = linspace(0,TRIG_90DEG,TRIG_DIV_NUM+1);
i = angle / (TRIG_90DEG/TRIG_DIV_NUM);
asin = TRIG_90DEG * sin(i/TRIG_DIV_NUM*90 * pi/180) + 0.5;
id = 0:32;
asin = [id' asin']

