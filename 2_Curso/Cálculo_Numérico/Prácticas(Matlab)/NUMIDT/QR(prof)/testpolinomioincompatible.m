f = @(x) x.^2 - 3*x + 1;
s = -5:0.1:5;
b = f(s) + randn(size(s));
polinomioincompatible(b,s,3)