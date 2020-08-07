function [p, difDiv] = polNewton(f, Xvector, a)
    % Comprobando que Xvector es un vector %
    [r, c] = size(Xvector);
    if r~=1 && c~=1
        error('dimensión Xvector incorrecta');
    end
    
    % difDiv es la diagonal de la matriz de diferencias dividadas,
    % la cual no la necesitamos y lo la hemos atrapado
    [~, difDiv] = difDivididas(f, Xvector); 
    
    n = length(Xvector);
    
    newt = 1;
    p = difDiv(1, 1)*newt;
    
    for j = 2:n
       newt = newt .* (a - Xvector(j-1));
       p = p + difDiv(j)*newt;
    end
    
end