function [L, U, err] = factLU(A)
    [r, c] = size(A);
    if r~=c
       error('Matriz no cuadrada');
    end

    n = r;
    U = A;
    L = eye(n);

    for k = 1: n-1
        if U(k,k) == 0
            error('U(k,k) igual a cero al paso %d', k);
        end
        for i = k+1:n
            L(i, k) = U(i, k)/U(k,k);

            % ---- MÉTODO CON FOR ----- %
            %for j = k:n  %%Si queremos que U sea triangular alta, k:n ; sino k+1:n
            %    U(i,j) = U(i, j) - (L(i,k)*U(k,j));
            %end

            % ----- USANDO VECTORIZACIÓN CON LOS MÉTODOS DE MATLAB ----
            U(i, k:n) = U(i, k:n) - L(i,k)*U(k, k:n);
        end
    end

    % OBSERVACIÓN : %
    % Podríamos hacer el for de j = k+1:n
    % U no sería triangular alta, pero podríamos usar la función:
    % U = triu(U); en este lugar, así podríamos versatilizar
    % esta función dependiendo de si queremos resolver un sistema
    % o factorizar A

    err = max(max(abs(A - L*U)));
end
