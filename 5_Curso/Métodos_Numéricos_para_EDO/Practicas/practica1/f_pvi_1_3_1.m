%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Variables de entrada:
%       t: escalar
%       u: vector columna de tamanio 2
%   
%   Variables de salida:
%       y: vector columna de tamanio 2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function y = f_pvi_1_3_1(t,u)
    A = [-2 1; 1 -2];
    y = A*u + 2*[sin(t); cos(t)-sin(t)];
end