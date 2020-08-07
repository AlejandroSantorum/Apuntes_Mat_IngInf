function I = Icompab(f,a,w,x)

N = length(a); I = 0;
for k=1:N-1
    I = I + Iab(f,a(k),a(k+1),w,x);
end

end