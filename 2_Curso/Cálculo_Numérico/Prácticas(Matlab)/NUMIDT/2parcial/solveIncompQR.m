function [X] = solveIncompQR(A, b)
    [n,m] = size(A);
    if m>n
        error('A tiene más columnas que filas');
    end
    if length(b) ~= n
        error('el vector b tiene que tener el mismo tamaño que el numero de filas de A')
    end
    if size(b,1) < size(b,2)
        b = b';
    end


    [Q,R] = factQR(A);

    % == Eso es lo que yo hice == %
    X = pinv(R) * Q' * b;

    % == El profesor hizo eso == %
    % y = Q'*b;
    % x = y./diag(R);
    % for i = m-1:-1:1
    %    for j = i+1:m
    %       x(i) = x(i) - R(i,j)*x(j)/R(i,i);
    %    end
    % end

end
