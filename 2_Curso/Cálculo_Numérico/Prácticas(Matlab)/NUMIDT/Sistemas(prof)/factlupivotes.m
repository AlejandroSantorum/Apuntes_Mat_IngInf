function [P,L,U,e] = factlupivotes(A)

[n, m] = size(A);
if n ~= m
    error('matriz no cuadrada');
end
U = A;
L = eye(n);
P = eye(n);

for k = 1:n-1
    [~,j] = max(abs(U(k:n,k)));    
    if j ~= 1
        r = j + k - 1; % ESTO ES EL i estrella
        v = P(k,:); P(k,:) = P(r,:); P(r,:) = v;
        v = U(k,k:n); U(k,k:n) = U(r,k:n); U(r,k:n) = v;
        v = L(k,1:k-1); L(k,1:k-1) = L(r,1:k-1); L(r,1:k-1) = v;
    end
    if U(k,k) == 0
        error('el pivot se ha anulado al paso %d', k)
    end
    for i=k+1:n
        L(i,k) = U(i,k)/U(k,k);
        U(i,k:n) = U(i,k:n) - L(i,k)*U(k,k:n);
    end
end

e = max(max(abs(P*A-L*U)));
end