function [sumat] = integSimple_ab(f, a, b, w, x)
    if(length(x) ~= length(w))
       error('tamaño del vector de pesos W distinto al vector de nodos X'); 
    end
    
    [rowX, colX] = size(x);
    [rowW, colW] = size(w);
    
    if(rowX > rowW) % X columna y W fila
        sumat = w * f(0.5*(b-a)*x + 0.5*(b+a));
    elseif(rowX < rowW) % X fila y W columna
        sumat = f(0.5*(b-a)*x + 0.5*(b+a)) * w;
    else
        if rowX > colX % X y W vectores columnas
            sumat = w' * f(0.5*(b-a)*x + 0.5*(b+a));
        else % X y W vectores fila
            sumat = f(0.5*(b-a)*x + 0.5*(b+a)) * w';
        end
    end
    
    %tam = length(x);
    
    %for i = 1:tam
    %    sumat = sumat + w(i)*f(0.5*(b-a)*x(i) + 0.5*(b+a));
    %end
    sumat = sumat*0.5*(b-a);
end