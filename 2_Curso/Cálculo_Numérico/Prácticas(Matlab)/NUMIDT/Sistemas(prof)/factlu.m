function [L,U,e] = factlu(A)

[n, m] = size(A);
if n ~= m
    error('matriz no cuadrada');
end

U = A;
L = eye(n);

for k = 1:n-1
    if U(k,k) == 0
        error('el pivot se ha anulado al paso %d', k)
    end
    for i=k+1:n
        L(i,k) = U(i,k)/U(k,k);
%         for j = k:n
%             U(i,j) = U(i,j) - L(i,k)*U(k,j);
%         end
        U(i,k:n) = U(i,k:n) - L(i,k)*U(k,k:n);
    end
end

e = max(max(abs(A-L*U)));

end