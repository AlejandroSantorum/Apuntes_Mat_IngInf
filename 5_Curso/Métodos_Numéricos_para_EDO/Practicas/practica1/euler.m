%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Esta funcion resuelve el problema de valor inicial
% u=f(t,u)
% u(t0)=u0
% utilizando el metodo de Euler
%
% [u,t]=euler(N,t0,T,u0)
%
% Variables de Entrada:
%   f: vector columna. funcion que rige el sistema de EDO,
%      tiene dos argumentos f(t,x) donde t es escalar
%   y x vector columna.
%   N: numero de pasos en los que dividimos el intervalo de
%      integracion
%   t0: tiempo inicial
%   T: tiempo final
%   u0: vector columna. Dato inicial
%
% Variables de Salida:
%   u: matriz de length(u0) x N que contiene la soluci´on
%   t: vector de tiempos
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [u,t]=euler(f,N,t0,T,u0)
    % Paso equidistante
    h = (T-t0)/N;
    % Vector de tiempos
    t = [t0:h:T];
    % Matriz de la solucion
    u = zeros(length(u0), length(t)); % length(t) = N+1
    u(:,1)=u0;
    
    % Aplicamos algoritmo de Euler: u(n+1) = u(n) + h*f(t(n),u(n))
    for n=1:N
        u(:,n+1) = u(:,n) + h*f(t(n), u(:,n));
    end
    
end


