function [X, err] = solveSistLUP(A, b)
    [P, L, U, ~] = factLUPivotaje(A);
    
    n = length(A);
    
    aux = size(b);
    if aux(1) > aux(2) %Comprobando si b es un vector fila o columna
        y = b;
    elseif aux(2) > aux(1)
        y = b';
    else
        error('b es una matriz cuadrada, no un vector');
    end
    
    % Único cambio realizado con respecto a su función
    % hermana, solveSistLU(). 
    % Obsérvese arriba que se usa factLUPivotaje() en
    % lugar de factLU(), por lo que cambian las variables
    % que devuelve.
    y = P*y;
    
    for i = 2:n
        %---- MÉTODO CON FOR ---- %
        %for j = 1:i-1
        %   y(i) = y(i) - L(i,j)*y(j);
        %end
        
        % --- USANDO VECTORIZACIÓN --- %
        y(i) = y(i) - L(i, 1:i-1)*y(1:i-1);
    end
    
    X = y./diag(U);
    for i = n:-1:1
        % ---- MÉTODO CON FOR --- %
        %for j = i+1:n
        %    X(i) = X(i) - ((U(i,j)*X(j))/U(i,i));
        %end
        
        % --- USANDO VECTORIZACIÓN --- %
        X(i) = X(i) - ((U(i, i+1:n)*X(i+1:n))/U(i,i));
    end
    
    if aux(1) > aux(2) %Comprobando si b es un vector fila o columna
        err = max(abs(A*X - b));
    elseif aux(2) > aux(1)
        err = max(abs(A*X - b'));
    end
end