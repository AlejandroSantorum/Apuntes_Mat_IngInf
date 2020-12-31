N = [100, 1000, 10000, 100000];
errores = zeros(1,4);

c = [0; 0.5; 1];
b = [1/6; 2/3; 1/6];
A = [0 0 0; 0.5 0 0; -1 2 0];

u0 = [2;3];

for i=1:4
    % calculo de la solucion aproximada
    [u,t] = RKexplicito(@f_pvi_1_3_1, N(i), 0, 10, u0, b, c, A);
    % calculo de la solucion exacta
    u_exac = f_pvi_1_3_2(t);
    err = u - u_exac;
    errores(i) = max(max(abs(err)));
end

h = 10./N;  % division elemento a elemento
loglog(h, errores); % escala logaritmica (en el eje X y en el Y)

% Calcular pendiente media de la recta
e1 = log10(errores);
h = log10(h);
p1 = zeros(3,1);
for i=1:3
   s = h(i+1)-h(i);
   p1(i) = (e1(i+1)-e1(i))/s;
end
sum(p1)/3