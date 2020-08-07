function [P, L, U, err] = factLUPivotaje(A)
    [r, c] = size(A);
    if r~=c
       error('Matriz no cuadrada'); 
    end
    
    n = r;
    L = eye(n);
    U = A;
    P = eye(n);
    
    for k = 1:n
        [~, pos] = max(abs(U(k:n, k)));
        if pos~=1
        % --------- LA CHICHA AQUÍ --------- %
            % Cambiando filas en U %
            aux = U(k,k:n);
            U(k,k:n) = U(pos+k-1, k:n);
            U(pos+k-1, k:n) = aux;
            
            % Cambiando filas en L %
            aux = L(k, 1:k-1);
            L(k, 1:k-1) = L(pos+k-1, 1:k-1);
            L(pos+k-1, 1:k-1) = aux;
            
            % Cambiando filas en P %
            aux = P(k, :);
            P(k, :) = P(pos+k-1, :);
            P(pos+k-1,:) = aux;
            
        end
        
        for i = k+1:n
            L(i,k) = U(i,k)/U(k,k);
            % ---- MÉTODO CON FOR ----- %
            %for j = k:n  %%Si queremos que U sea triangular alta, k:n ; sino k+1:n
            %    U(i,j) = U(i, j) - (L(i,k)*U(k,j)); 
            %end
            
            % ----- USANDO VECTORIZACIÓN CON LOS MÉTODOS DE MATLAB ---- 
            U(i, k:n) = U(i, k:n) - L(i,k)*U(k, k:n);
        end
        
    end
    
    err = max(max(abs(P*A - L*U)));
    
end
