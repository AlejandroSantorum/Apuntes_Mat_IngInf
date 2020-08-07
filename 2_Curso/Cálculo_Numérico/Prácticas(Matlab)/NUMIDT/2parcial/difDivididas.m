function [matriz, difDiv] = difDivididas(f, Xvector)
    % Comprobando que Xvector es un vector %
    [r, c] = size(Xvector);
    if r~=1 && c~=1
        error('dimensión Xvector incorrecta');
    end
    
    if r<c
        Xvector = Xvector';
    end
    
    n = length(Xvector);
    
    matriz = zeros(n);
    
    for i = 1:n %primera columna matriz
       matriz(i, 1) = f(Xvector(i)); 
    end
    
    for j = 2:n %resto de iteraciones
        %for k = j:n
        %    matriz(k, j) = (matriz(k, j-1) - matriz(k-1, j-1))/(Xvector(k) - Xvector(k-j+1));
        %end
        
        % vectorizado
        matriz(j:n, j) = (matriz(j:n, j-1) - matriz((j:n)-1, j-1))./(Xvector(j:n) - Xvector((j:n)-j+1));
    end
    
    difDiv = diag(matriz);        
end