function x = incompatible(A,b)

[n,m] = size(A);
if n < m
    error('La matriz no tiene rango maximo')
end
if length(b) ~= n
    error('Datos no asociados a un sistema lineal')
end
if size(b,2) > size(b,1); b = b'; end

[Q,R] = gramschmidt(A);

y = Q'*b;
x = y./diag(R);
for i = m-1:-1:1
    for j = i+1:m
        x(i) = x(i) - R(i,j)*x(j)/R(i,i);
    end
end


end