function [c, err, nIter] = busquedaPuntoFijo(g, x0, tol, maxIter)

    if nargin < 3
        tol = 10^-4;
    end

    if nargin < 4
        maxIter = 100;
    end

    err = 100;
    nIter = 0;

    while err > tol && nIter < maxIter
        nIter = nIter+1;
        x1 = g(x0);
        err = abs(x1-x0);
        x0=x1;
    end
    c = x0;
end
