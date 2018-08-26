clear;
clc;
format compact;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Example 2
%%   The function is the sequence x[n] = a^n u[n]. 
SampleN = 65;
InterpN = 512;
n = 0:SampleN-1;
Nt = 1.0;
f0 = 50;
fs = SampleN * f0 / Nt;
t = 0.0;
for i=0:SampleN-1
    x(i+1) = 128+128*sin(0.8*i)*cos(0.1*i);
    %x(i+1) = 128+128*sin(2.*pi*f0*t);
    t = t + 1.0/fs;
end
%%   Sampled values
figure(1);
plot(n,x);
title('原始信号');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Interpolations
%%   The black curve is the Matlab interp method. The blue curve is sinc interpolation. The circles are sample values. 
for i=0:InterpN-1
    s(i+1) = i*(SampleN-1)/InterpN;
end
x2 = sinc_interp(x, SampleN, InterpN);
figure(2);
plot(n,x,s(1:InterpN),x2(1:InterpN));
%hold
%xi = interp1(n,x,s);
%plot(s(1:512),xi(1:512),'k');
%plot(n(1:N),x(1:N),'o');
%hold off
title('正弦插值后');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%