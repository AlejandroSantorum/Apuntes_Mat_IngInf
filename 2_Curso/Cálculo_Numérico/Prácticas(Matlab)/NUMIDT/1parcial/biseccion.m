function [c, err, n_iter] = biseccion(f, a, b, E)


    if(f(a) * f(b) > 0)
        error('El intervalo no es óptimo');
    end

    n_iter=0;
    err = abs(b-a);
    if(err < E)
        error('Intervalo menor que la tolerancia');
    end

    if(abs(f(a)) < eps)
        c = a;
        err = a;
        return
    end
    if(abs(f(b)) < eps)
        c = b;
        err = b;
        return
    end

    c = 0.5*(b+a);
    if abs(f(c))<eps
        err = abs(f(c));
        return
    end

    while (err > E)
        c = (a + b)/2;
        n_iter = n_iter + 1;
        if(abs(f(c))<eps)
            return
        end
        if (f(c) * f(a) < 0)
            b = c;
        else
            a = c;
        end
        err = abs(b-a);
    end
end
