function [LAMBDA,NIt] = autovaloresQR(A,tol,MaxIt)

if size(A,1) ~= size(A,2)
    error('Se necesita una matriz cuadrada')
end
if max(max(abs(A - A'))) ~= 0
    error('Se necesita una matriz hermitica')
end

esdiagonal = @(A) abs( max(max(abs(A - diag(diag(A)))))/max(abs(diag(A))) ) < tol;

NIt = 0;
while NIt < MaxIt && ~esdiagonal(A)
    NIt   = NIt + 1;
    [Q,R] = gramschmidt(A);
    A     = R*Q;
end

LAMBDA = diag(A);

end