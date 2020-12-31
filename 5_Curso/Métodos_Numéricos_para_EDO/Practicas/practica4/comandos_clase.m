[t,y] = ode45(@f_pvi_1_3_1, [0 20], [2;3]);
% grafica solucion
plot(y(:,1), y(:,2))
% grafica de h's (varian a lo largo del algoritmo)
plot(t(2:end) - t(1:end-1))

% solucion exacta
y_exact = f_pvi_1_3_2(t);
% error
error = max(max(y_exact - y))

% ode statistics
opc = odeset('Stats', 'on');
[t,y] = ode45(@f_pvi_1_3_1, [0 20], [2;3], opc);
error = max(max(y_exact - y))

[t,y] = ode45(@f_pvi_1_3_1, [0:20], [2;3], opc);

opc1 = odeset('Stats', 'on', 'AbsTol', 10^(-10), 'RelTol', 10^(-10));
[t,y] = ode45(@f_pvi_1_3_1, [0 20], [2;3], opc1);
plot(t(2:end) - t(1:end-1))

[t,y] = ode45(@f_pvi_2, [0 20], [2;3], opc);
y_exact = f_pvi_1_3_2(t);
error = max(max(y_exact - y))

[t,y] = ode23(@f_pvi_1_3_1, [0 20], [2;3], opc);
y_exact = f_pvi_1_3_2(t);
error = max(max(y_exact - y))

[t,y] = ode23(@f_pvi_2, [0 20], [2;3], opc);
y_exact = f_pvi_1_3_2(t);
error = max(max(y_exact - y))

[t,y] = ode113(@f_pvi_1_3_1, [0 20], [2;3], opc);
y_exact = f_pvi_1_3_2(t);
error = max(max(y_exact - y))

[t,y] = ode113(@f_pvi_2, [0 20], [2;3], opc);
y_exact = f_pvi_1_3_2(t);
error = max(max(y_exact - y))



