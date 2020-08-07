function [] = graficaPolLagrange(f, Xvector)
    [r, c] = size(Xvector);
    if r~=1 && c~=1
        error('dimensión Xvector incorrecta');
    end

    n = length(Xvector);
    Yvector = f(Xvector); % f tiene que servir para vectores

    if(Xvector(n) < Xvector(1))
      auxV = Xvector(n):0.1:Xvector(1);
    else
      auxV = Xvector(1):0.1:Xvector(n);
    end

    m = length(auxV);
    Pvector = ones(1, m);

    for i = 1:m
        Pvector(i) = polLagrange(Xvector, Yvector, auxV(i));
    end

    fplot(f, [Xvector(1) , Xvector(n)], 'r');
    hold on;
    plot(auxV, Pvector, 'b');
    plot(Xvector, Yvector, '*m');
    str = {'Rojo: funcion real f', 'Azul: polinomio Lag aprox', 'Magenta: nodos'};
    dim = [ .2 .5 .3 .3];
    annotation('textbox', dim, 'String', str, 'FitBoxToText', 'on');
end
