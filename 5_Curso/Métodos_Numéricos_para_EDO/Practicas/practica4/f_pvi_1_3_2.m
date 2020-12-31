%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   Variables de entrada:
%       t: vector fila de tamanio N
%   
%   Variables de salida:
%       u: matriz de tamanio 2xN
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function u = f_pvi_1_3_2(t)
    u = [2*exp(-t) + sin(t) , 2*exp(-t) + cos(t)];
end