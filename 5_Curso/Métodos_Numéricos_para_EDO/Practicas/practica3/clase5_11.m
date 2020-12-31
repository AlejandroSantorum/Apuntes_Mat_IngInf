
% 1 paso
[u, t, niter] = RKImplicito_quasiNewton(@f_pvi_1_3_1, @df1, 200, 0, 10, [2;3], 1, 0.5, 0.5, 100, 10^(-8));
plot(u(1,:), u(2,:))
sol_exac = f_pvi_1_3_2(t);
max(max(u-sol_exac))

% 2 pasos
c = [0;1];
b=[1/2; 1/2];
A=[0 0; 1/2 1/2];
[u, t, niter] = RKImplicito_quasiNewton(@f_pvi_1_3_1, @df1, 200, 0, 10, [2;3], b, c, A, 100, 10^(-8));
max(max(u-sol_exac))

max(niter)

[u, t, niter] = RKImplicito_quasiNewton(@f_pvi_2, @df2, 200, 0, 10, [2;3], b, c, A, 100, 10^(-8));

