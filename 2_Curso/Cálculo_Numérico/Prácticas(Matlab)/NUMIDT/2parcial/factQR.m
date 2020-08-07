function [Q, R] = factQR(A)

    [n,m] = size(A);
    if m>n
        error('Matriz A con más columnas que filas');
    end
    Q = zeros(n,m);
    R = zeros(m,m);
    
    R(1,1) = norm(A(:, 1));
    Q(:, 1) = A(:, 1)./R(1,1);
    
    for k = 2:m
        vector = A(:,k);
        for j = 1:k-1
            % ---- Utilizando dot ----
            R(j,k) = dot(Q(:,j), A(:,k));
            
            % ---- Sabemos las dimensiones:
            % con esta implementación podemos
            % usar valores complejos ----
            %R(j,k) = Q(:,j)' * A(:,k);
            
            vector = vector - R(j,k).*Q(:,j);
        end
        R(k,k) = norm(vector);
        Q(:,k) = vector./R(k,k);
    end
end