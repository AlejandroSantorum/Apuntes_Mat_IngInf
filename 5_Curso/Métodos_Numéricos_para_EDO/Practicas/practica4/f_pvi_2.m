%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Variables de entrada:
%       t: vector tamanio s
%       u: vector columna de tamanio 2s
%   
%   Variables de salida:
%       y: vector columna de tamanio 2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function y = f_pvi_2(t,u)
    s = length(t);
    y = zeros(2*s,1);
    A = [-2 1; 998 -999];
    for i=1:s
        y(2*i-1:2*i) = A*u(2*i-1:2*i) + [2*sin(t(i)); 999*(cos(t(i))-sin(t(i)))];
    end
end