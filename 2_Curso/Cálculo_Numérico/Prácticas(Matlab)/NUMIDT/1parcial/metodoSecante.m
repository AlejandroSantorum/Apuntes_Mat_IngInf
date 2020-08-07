function [root, err, nIter] = metodoSecante(f, x1, x0, tol1, tol2, maxIter)
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
    N = (x1 - x0) * f(x1);
    D = f(x1) - f(x0);
    if D == 0
            error('Denominador igual a cero.')
    end
    err = abs(f(x1));
    
    while (err > tol1) && (abs(N/D) > tol2) && (nIter < maxIter)
        nIter = nIter+1;
        N = (x1 - x0) * f(x1);
        D = f(x1) - f(x0);
        if D == 0
            error('Denominador igual a cero.')
        end
        x2 = x1 - (N/D);
        x0 = x1;
        x1 = x2;
        err = abs(f(x1));
    end
    root = x1;
end