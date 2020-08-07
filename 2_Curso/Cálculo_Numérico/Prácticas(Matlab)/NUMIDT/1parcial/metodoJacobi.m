% Alejandro Santorum Varela
% metodoJacobi.m version 1
% 13-03-2018
%====================================================================%
% Queremos resolver el sistema Ax = b con la iteracion de Jacobi
% EL método iterativo x = Bx + v se define como:
% B = D(A)^(-1) * D(A) donde D(A) es la matriz diagonal de A,
%  y v = D(A)^(-1) * b. La convergencia se caracteriza entonces con
% el radio espectral de B.
%====================================================================%
function [x, err, nIter] = metodoJacobi(A, b, tol, iterMax)
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
    
    % D es la matriz que contiene en su diagonal
    % los elementos de la diagonal de A.
    % El resto de elementos de D (fuera de la diagonal)
    % son ceros. 
    D = diag(diag(A)); 
    % D = diag(diag(A)),
    % pero D^-1 es el inverso
    % de los elementos de la diagonal de D
    D1 = diag(1./diag(A));
    
    while(err > tol && nIter < iterMax)
        nIter = nIter + 1;
        
        % == ITERACION JACOBI == %
        x1 = D1*(b - (A - D)*x);
        % ---------------------- %
        
        err = max(abs(x1 - x)); % Norma infinito
                                % la Norma 2 se haria asi:
                                % err = norm(A*x - b);
        x = x1;
    end
        
end