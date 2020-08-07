function [c,n] = puntofijo(g,x0,tol,MaxIt)

if nargin < 3
    tol   = 1e-4; % esto es 10^-4
end

if nargin < 4
    MaxIt = 100;
end

n = 0;
x = x0;
E = abs(g(x)-x);

while E > tol && n < MaxIt
    n = n + 1;
    x = g(x);
    E = abs(g(x)-x);
end

c = x;

end