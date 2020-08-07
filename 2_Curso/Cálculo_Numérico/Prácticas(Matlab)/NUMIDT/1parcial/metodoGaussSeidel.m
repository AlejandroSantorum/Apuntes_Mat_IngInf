function [x, err, nIter] = metodoGaussSeidel(A, b, tol, maxIter)
    [m,n] = size(A);
    l = length(b);
    % ===== ERROR CHECKING ===== %
    if m~=n
        error('Matriz A no cuadrada');
    end
    if m~=l
        error('la matriz A tiene más filas que el tamaño del vector b');
    end
    % -------------------------- %
    
    % === COMPROBANDO QUE A ES UNA MATRIZ DOMINADA POR LA DIAGONAL == %
    
    for i = 1:n
       aux = 0;
       d = abs(A(i,i));
       for j = 1:n
           aux = aux + abs(A(i, j));
       end
       aux = aux - d;
       if aux >= d
          fprintf('A no es una matriz dominada por la diagonal\n');
          break 
       end
    end
    %-----------------------------------------------------------------%
    
    % ======= Si b es un vector fila, lo pasamos a columna ===== %
    tam = size(b);
    if tam(2) > tam(1) %Comprobando si b es un vector fila
        b = b';
    elseif tam(1) == tam(2)
        error('b es una matriz cuadrada, no un vector');
    end
    % --------------------------------------------------------- %
    
    err = 1000;
    nIter = 0;
    x = ones(l, 1);
    x1 = x;
    
    while(err > tol && nIter < maxIter)
       nIter = nIter + 1;
       for i = 1:n
           sumat1 = 0;
           sumat2 = 0;
           for j = 1:i-1
               sumat1 = sumat1 + A(i,j)*x1(j);
           end
           for j = i+1:n
               sumat2 = sumat2 + A(i,j)*x(j);
           end
           % == ITERACIÓN DE GAUSS-SEIDEL == %
           % sumat1 y sumat2 calculados en los fors anteriores
           x1(i) = (b(i) - sumat1 - sumat2)/A(i,i);    
       end
       err = max(abs(x1 - x));% Norma infinito
                              % la Norma 2 se haria asi:
                              % err = norm(A*x - b);
       x  = x1;
    end
end