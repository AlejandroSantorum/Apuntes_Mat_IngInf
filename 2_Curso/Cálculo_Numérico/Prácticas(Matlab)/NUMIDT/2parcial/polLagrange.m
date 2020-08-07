function [p] = polLagrange(Xvector, Yvector, a)
    % Comprobando que Xvector e Yvector son vectores %
    [r, c] = size(Xvector);
    if r~=1 && c~=1
        error('dimensión Xvector incorrecta');
    end
    [r, c] = size(Yvector);
    if r~=1 && c~=1
        error('dimensión Yvector incorrecta');
    end
    % ============================================== %
    
    auxV = Lj(Xvector, a); %auxV es vector columna
    
    
    p = dot(auxV, Yvector); % dot() hace el producto escalar.
                            % Dentro ya hace las comprobaciones de las
                            % dimensiones
    % Podriamos haber hecho nosotros el producto escalar vectorizando
    % auxV * Yvector, pero tendríamos que hacer las comprobaciones de
    % dimensión del vector Y, ya que dependiendo de si es fila o columna
    % tendríamos que hacer Yvector*auxV ó auxV' * Yvector respectivamente.
end