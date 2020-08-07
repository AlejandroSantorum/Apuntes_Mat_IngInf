function [autovalores, nIter] = autovaloresQR(A, tol, maxIter)
    if size(A,1) ~= size(A,2)
        error('Se necesita una matriz cuadrada')
    end
    if max(max(abs(A - A'))) ~= 0
        error('Se necesita una matriz hermitica ')
    end
    
    nIter = 0;
    while(nIter < maxIter)
        nIter = nIter + 1;
        
        % == Comprobación de parada si la matriz A es diagonal == %
        B = abs(A - diag(diag(A)));
        if max(max(B)) < tol
            break;
        end
        % ======================================================== %
        
        [Q,R] = factQR(A);
        A = R*Q;  
    end
    autovalores = diag(A);
end