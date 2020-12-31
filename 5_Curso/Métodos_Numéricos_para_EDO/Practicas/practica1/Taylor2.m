%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Esta funcion resuelve el problema de valor inicial
% u?=f(t,u)
% u(t0)=u0
% utilizandodo un metodo de Taylor de orden 2
%
% [u,t]=Taylor2(f,df,Jf,T,t0,N,u0,b,c,A)
%
% Variables de Entrada:
% f: vector columna. funcion que rige el sistema de EDO,
%       tiene dos argumentos f(t,x) donde t es escalar
%       y x vector columna.
% df: vector columna. funci´on derivada parcial con respecto,
%       al tiempo de f, tiene dos argumentos df(t,x) donde
%       t es escalar y x vector columna.
% Df: matriz cuadrada. funci´on jacobiano con respecto a x de
%       f, tiene dos argumentos Df(t,x) donde t es escalar
%       y x vector columna.
% N: numero de pasos en los que dividimos el intervalo de
%       integracion
% t0: tiempo inicial
% T: tiempo final
% u0: vector columna, dato inicial
%
% Variables de Salida:
% u: matriz de length(u0) x length(t) que contiene la solucion
% t: vector de tiempos
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [u,t]=Taylor2(f,df,Jf,T,t0,N,u0)
    % paso equidistante
    h = (T - t0)/N;
    % vector de tiempos
    t = [t0:h:T];
    % matriz solucion numerica
    u = zeros(length(u0), N+1);
    % incorporamos el dato inicial a mi solucion numerica
    u(:,1) = u0;

    % aplicamos ahora el algoritmo de taylor de orden 2
    I = eye(length(u0));
    for n=1:N
        u(:,n+1) = u(:,n) + h*(I+0.5*h*Jf(t(n),u(:,n)))*f(t(n), u(:,n)) + 0.5*h^2*df(t(n), u(:,n));
    end

end



