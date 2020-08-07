function [root, err, nIter] = metodoNewton(f, df, x0, tol1, tol2, maxIter)
    if nargin < 3
        error('Número de parámetros insuficientes.')
    end
    
    if nargin < 4
        tol1 = eps;
    end
    if nargin < 5
        tol2 = eps;
    end
    if nargin < 6
        maxIter = 1000;
    end
    
    nIter = 0;
    F = f(x0);
    D = df(x0);
    if D == 0
            error('Derivada igual a cero.')
    end
    err = abs(F/D);
    
    while (abs(F) > tol1) && (err > tol2) && (nIter < maxIter)
        nIter = nIter+1;
        F = f(x0);
        D = df(x0);
        if D == 0
            error('Derivada igual a cero.')
        end
        x0 = x0 - (F/D);
        err = abs(F/D);
    end
    root = x0;
end