close all; clear; clc

%f = @(x) exp(-x.^2);
%f = @(x) cos(0.5*pi*x);
f = @(x) 1./(1 + x.^2); % Función de Runge
a = -5;
b = 5;
n = 5;

% Nodos equiespaciados : 
% s = a + (0:n)*(b-a)/n;
% ======================

% Nodos de Chebyshev :
%t = cos(0.5 * pi * (2*(0:n)+1)/(n+1)); % en [-1, 1]
s = 0.5 * (b-a)*(cos(0.5 * pi * (2*(0:n)+1)/(n+1))) + 0.5 * (b+a);
% =======================================

graficaPolLagrange(f, s);
