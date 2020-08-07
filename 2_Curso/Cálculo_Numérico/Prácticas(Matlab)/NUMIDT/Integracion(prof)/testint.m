clear; close all; clc

% f = @(x) x.^5 + 37*x.^2 - 12;
% a = -7; b = 11;

f = @(x) 1./(1+x.^2);
a = -5; b = 5;

TOP = 15;
for N = 2:TOP
v = a:(b-a)/(N-1):b; % N puntos equiespaciados entre a y b

[Im(N),It(N),Is(N),I2(N),I3(N)] = integracion(f,v);

end

figure
subplot(2,2,1); plot(2:TOP,Im(2:TOP))
subplot(2,2,2); plot(2:TOP,Is(2:TOP))
subplot(2,2,3); plot(2:TOP,I2(2:TOP))
subplot(2,2,4); plot(2:TOP,I3(2:TOP))

I = I3(TOP);

Em(2:TOP) = abs(Im(2:TOP)-I);
Et(2:TOP) = abs(It(2:TOP)-I);
Es(2:TOP) = abs(Is(2:TOP)-I);
E2(2:TOP) = abs(I2(2:TOP)-I);
E3(2:TOP) = abs(I3(2:TOP)-I);

figure
subplot(2,2,1); plot(2:TOP,log10(Em(2:TOP)))
subplot(2,2,2); plot(2:TOP,log10(Es(2:TOP)))
subplot(2,2,3); plot(2:TOP,log10(E2(2:TOP)))
subplot(2,2,4); plot(2:TOP,log10(E3(2:TOP)))