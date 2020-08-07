function I = Iab(f,a,b,w,x)

u = @(t) 0.5*((b-a)*t + b + a);

n = length(w); I = 0;
for j = 1:n
    I = I + w(j)*f(u(x(j)));
end

% I = dot(w,f(u(x)));

I = 0.5*I*(b-a);

end