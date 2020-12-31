N = [100, 1000, 10000, 100000, 1000000];
err1 = zeros(1,5); % error Euler
err2 = zeros(1,5); % error Taylor 2

for i=1:5
    % calculo de la solucion aproximada (Euler)
    [u,t] = euler(@f_pvi_1_3_1, N(i), 0, 10, [2;3]);
    % calculo de la solucion aproximada (Taylor 2)
    [v,t] = Taylor2(@f_pvi_1_3_1, @df1, @Jf1, 10, 0, N(i), [2;3]);
    % calculo de la solucion exacta
    u_exac = f_pvi_1_3_2(t);
    err1(i) = max(max(abs(u-u_exac)));
    err2(i) = max(max(abs(v-u_exac)));
end

h = 10./N;  % division elemento a elemento
loglog(h, err1); % escala logaritmica (en el eje X y en el Y)
hold on;
loglog(h, err2); % escala logaritmica (en el eje X y en el Y)

% Calcular pendiente media de la recta
e1 = log10(err1);
e2 = log10(err2);
h = log10(h);
p1 = zeros(4,1);
p2 = zeros(4,1);
for i=1:4
   s = h(i+1)-h(i);
   p1(i) = (e1(i+1)-e1(i))/s;
   p2(i) = (e2(i+1)-e2(i))/s;
end
sum(p1)/4
sum(p2)/4