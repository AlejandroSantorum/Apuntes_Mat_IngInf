% u = (S; I; R) --> u' = y = (S'; I'; R')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Variables de entrada:
%       t: escalar
%       u: vector columna de tamanio 3
%   
%   Variables de salida:
%       y: vector columna de tamanio 3
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function y = f_pvi_1_3_5_euler(t, u)
    % definimos las constantes alpha y beta segun el enunciado
    alpha = 0.5;
    beta = 0.005*alpha;
    % salida
    y = [-beta*u(1)*u(2); beta*u(1)*u(2) - alpha*u(2); alpha*u(2)];
end