function a = polinomioincompatible(b,s,m)

if size(b,2) > size(b,1); b = b'; end
n = length(b);

V(:,1) = ones(n,1);
for k = 2:m
    V(:,k) = s.^(k-1);
end

a = incompatible(V,b);

x = min(s):(max(s)-min(s))/1000:max(s);
for i = 1:length(x)
    p(i) = 0;
    for k = 1:m
        p(i) = p(i) + a(k)*x(i)^(k-1);
    end
end

figure
plot(s,b,'*r')
hold on
plot(x,p)

end