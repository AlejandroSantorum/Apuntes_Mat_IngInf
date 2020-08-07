function grafica_h(f, x0)

    for h = 1:60
        y(h) = d(f,x0, 2^-h);
    end
    
    plot(y)
    ylabel('derivada(h)');
    xlabel('h^-1');
    
end