clear; close all; clc;
a = 0;
b = 12;

u = @(t) 0.5*(t*(b-a) + b+a);

n = 50; %numero de nodos

%Nodos equiespaciados en [-1, 1] a [a,b]
%t = -1:2/(n-1):1;

%Nodos de Chebyshev en [-1, 1]
t = cos(0.5*pi*((2*(1:n)-1)/n));

s = u(t);

x = a:(b-1)/(10000):b;

f = @(x) sin(7*x);

p = polNewton(f, s, x);

plot(x,p); hold on; plot(x, f(x), 'k'); plot(s, f(s), '*r');
