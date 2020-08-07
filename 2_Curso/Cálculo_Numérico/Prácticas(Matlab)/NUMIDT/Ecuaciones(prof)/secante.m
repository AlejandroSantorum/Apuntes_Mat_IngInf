function [x,E,n] = secante(f,x,y,tol1,tol2,MaxIt)

n = 0;

E = abs(f(x));
N = f(x)*(x-y);
D = f(x)-f(y);
if D == 0
	error('hemos encontrado un cero en el denominador')
end

while E > tol1 && abs(N/D) > tol2 && n < MaxIt
    
    N = f(x)*(x-y);
    D = f(x)-f(y);
    if D == 0
        error('hemos encontrado un cero en el denominador')
    end

    y = x;
    x = x - N/D;
    n = n+1;
    E = abs(f(x));
    
end

E = abs(f(x));

end