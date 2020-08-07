
MaxIt = 100;
tol   = 1e-4; % esto es 10^-4

f = @(x) x.^7 + 11*x - 1;
lambda = 0.05;
g = @(x) x - lambda*f(x);

n = 0;
x = 0.5;
E = abs(g(x)-x);

while E > tol && n < MaxIt
    n = n + 1;
    x = g(x);
    E = abs(g(x)-x);
end

n
E
x