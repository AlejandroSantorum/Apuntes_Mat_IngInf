%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Esta funcion resuelve el problema de valor inicial
% Y?=f(t,Y)
% Y(t0)=y0
% utilizandodo un metodo Runge-Kutta expl´?cito
%
% [y,t]=RKexplicito(f,N,t0,T,u0,b,c,A)
%
% Variables de Entrada:
%
% f: vector columna. funcion que rige el sistema de EDO,
% tiene dos argumentos f(t,x) donde t es escalar
% y x vector columna.
% N: numero de pasos en los que dividimos el intervalo de
% integracion
% t0: tiempo inicial
% T: tiempo final
% y0: vector columna, dato inicial
% b,c,A: coeficientes del tablero de BUTCHER.
% A: matriz cuadrada de orden s
% b,c: vectores columna de orden s (b vector de pesos, c vector de nodos)
%
% Variables de Salida:
%
% y: matriz de length(u0) x length(t) que contiene la solucion
% t: vector de tiempos
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [u,t] = RKexplicito(f,N,t0,T,u0,b,c,A)
    % Paso equidistante
    h = (T-t0)/N;
    % Vector de tiempos
    t = [t0:h:T];
    % Matriz de la solucion
    d = length(u0);
    u = zeros(d,N+1);
    % Incorporamos el dato inicial en mi solucion numerica
    u(:,1) = u0;
    s = length(c);
    k = zeros(d,s);
    
    % Aplicamos algoritmo de RK
    for n=1:N
        k(:,1) = f(t(n), u(:,n));
        for i=2:s
            k(:,i) = f(t(n)+c(i)*h, u(:,n)+h*k(:,1:i-1)*A(i,1:i-1)');
        end
        u(:,n+1) = u(:,n) + h*k*b;
    end
end


