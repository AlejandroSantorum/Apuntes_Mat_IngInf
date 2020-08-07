function [X, err] = solveSistLU(A, b)
    [L, U, ~] = factLU(A);
    
    n = length(A);
    
    y = b;
    for i = 2:n
        % ---- MÉTODO CON FOR ---- %
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
    
    err = max(abs(A*X - b));
end