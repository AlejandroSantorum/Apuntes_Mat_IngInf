function [c, err, n_iter] = punto_fijo(f, x0, lambda, E, maxIt)
    g = @(x) x - lambda*f(x);

    n_iter = 0;
    err = 1;
    while err > E && n_iter < maxIt
        n_inter = n_iter + 1;
        x1 = g(x0);
        err = abs(x1-x0);
        x0 = x1;
    end
    c = x1;
end
