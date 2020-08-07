function [x,e] = sistemaLU(A,b)

n = size(A,1);

[L,U] = factlu(A);

y = b;
for i = 2:n
    for j = 1:i-1
        y(i) = y(i) - L(i,j)*y(j);
    end
end

x = y./diag(U);
for i = n-1:-1:1
    for j = i+1:n
        x(i) = x(i) - U(i,j)*x(j)/U(i,i);
    end
end

e = max(abs(A*x - b));

end