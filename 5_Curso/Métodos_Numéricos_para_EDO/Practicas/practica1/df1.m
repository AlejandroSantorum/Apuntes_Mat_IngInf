%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Variables de entrada:
%       t: escalar
%       u: vector columna de tamanio 2
%   
%   Variables de salida:
%       y: vector columna de tamanio 2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function y = df1(t,u)
    y = -2*[-cos(t); cos(t)+sin(t)];
end