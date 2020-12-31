N = [100, 1000, 10000, 100000, 1000000];
err1 = zeros(1,5); % error absoluto en T
err2 = zeros(1,5); % error absoluto para todo t

for i=1:5
    % calculo de la solucion aproximada
    [u,t] = euler(@f_pvi_1_3_1, N(i), 0, 10, [2;3]);
    % calculo de la solucion exacta
    u_exac = f_pvi_1_3_2(t);
    err = u - u_exac;
    err1(i) = max(abs(err(:,N(i)+1)));
    err2(i) = max(max(abs(err)));
end

h = 10./N;  % division elemento a elemento
loglog(h, err1); % escala logaritmica (en el eje X y en el Y)
hold on;
loglog(h, err2); % escala logaritmica (en el eje X y en el Y)
