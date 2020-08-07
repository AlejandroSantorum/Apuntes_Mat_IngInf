function [x,E,n] = nnewt(f,df,x,tol1,tol2,MaxIt)

% f  = @(x) x.^11 - 27 * x.^5 + 3;
% df = @(x) 11*x.^10 - 135*x.^4;
% x     = 0.9;
% tol1  = 1e-4;
% tol2  = 1e-4;
% MaxIt = 100;

n = 0;
F = f(x);
D = df(x);
if D == 0
	error('hemos encontrado un cero de la derivada')
end
while abs(F) > tol1 && abs(F/D) > tol2 && n < MaxIt
    F = f(x);
    D = df(x);
    if D == 0
        error('hemos encontrado un cero de la derivada')
    end
    x = x - F/D;
    n = n+1;
end

E = abs(F);

% figure(1)
% subplot(2,1,1); fplot(f,[-1,1]); grid on
% subplot(2,1,2); fplot(df,[-1,1]); grid on
% figure(2)
% subplot(2,1,1); fplot(f,[-2,2]); grid on
% subplot(2,1,2); fplot(df,[-2,2]); grid on

end