
clear;clc;
close all;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Example 1
%%   The function is the sequence x[n] = n a^n u[n]. 
%%   Sampled values   %%
a = 0.9;
N = 64+1;
n = 0:N-1;
x = n.*a.^n;
figure(11);
plot(n,x);
title('原始采样信号');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Magnitude of Fourier transform
%%   The function is essentially band-limited
y = fft(x);
k= 0:N/2;
figure(12);
plot(k/N,abs(y(1:N/2+1)));
title('FFT频谱');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Interpolations
%%   The black curve is the Matlab interp method. The blue curve is sinc interpolation. The circles are sample values. 
s = linspace(0,N-1,512);
x2 = sinc_interp(x,N,length(s));
figure(13);
plot(s(1:512),x2(1:512));
hold
xi = interp1(n,x,s);
plot(s(1:512),xi(1:512),'k');
plot(n(1:N),x(1:N),'o');
hold off
title('正弦插值后');
%%   The first half of the data is shown.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Interpolation difference
%%   The following shows the difference between the two interpolation methods.
figure(14);
plot(s,xi-x2);
ylabel('difference');
xlabel('duration');
title('相对误差');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Example 2
%%   The function is the sequence x[n] = a^n u[n]. 
N = 64+1;
n = 0:N-1;
x = sin(0.8*n).*cos(0.1*n);
%%   Sampled values
figure(21);
plot(n,x);
title('原始信号');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Magnitude of Fourier transform
%%   The function is essentially band-limited
y = fft(x);
k= 0:N/2;
figure(22);
plot(k/N,abs(y(1:N/2+1)));
title('FFT频谱');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Interpolations
%%   The black curve is the Matlab interp method. The blue curve is sinc interpolation. The circles are sample values. 
s = linspace(0,N-1,512);

x2 = sinc_interp(x,N,length(s));
figure(23);
%plot(s(1:512),x2(1:512));
plot(n,x, s(1:512),x2(1:512));
%hold
%xi = interp1(n,x,s);
%plot(s(1:512),xi(1:512),'k');
%plot(n(1:N),x(1:N),'o');
%hold off
title('正弦插值后');
%grid;
%%   The first half of the data is shown.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%   Interpolation difference
%%   The following shows the difference between the two interpolation methods.
figure(24);
plot(s,xi-x2);
ylabel('difference');
xlabel('duration');
title('相对误差');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close figure 11;
close figure 12;
close figure 13;
close figure 14;
close figure 22;
close figure 24;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


