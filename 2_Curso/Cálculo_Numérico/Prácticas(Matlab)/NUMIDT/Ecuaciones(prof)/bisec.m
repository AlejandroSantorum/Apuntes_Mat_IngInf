function [c,err,n] = bisec(f,a,b,tol)

if f(a)*f(b) > 0
    error('No se cumplen las condiciones suficientes')
end
n = 0;
if abs(f(a)) < eps
    c = a; err = abs(f(c));
    return
elseif abs(f(b)) < eps
    c = b; err = abs(f(c));
    return
end
c = 0.5*(b+a);
if abs(f(c))<eps
    err = abs(f(c));
    return
end
while abs(b - a) > tol
   n = n +1;
   if f(a)*f(c) < 0
       b = c;
   elseif f(b)*f(c) < 0
       a = c;
   end
   c = 0.5*(b+a);
   if abs(f(c))<eps
       err = abs(f(c));
       return
   end
end
err = abs(f(c));
end