function [r, ERR] = mixmix(x,n)

% esta función calcula la exponencial de x
% con la formula de Taylor al orden n

r    = zeros(n+1,1);

r(1) = 1;

for k=1:n
    
    r(k+1) = r(k) + x^k/factorial(k);
    
end

ERR = exp(x) - r;

end