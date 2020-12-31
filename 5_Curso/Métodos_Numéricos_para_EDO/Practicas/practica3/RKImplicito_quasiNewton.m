%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Esta funcion resuelve el problema de valor inicial
% Y?=f(t,Y)
% Y(t0)=y0
% utilizandodo un metodo Runge-Kutta implicito con una iteracion quasi Newton
%
% [y,t]=RKImplicito_quasiNewton(f,df, N,t0,T,u0,b,c,A, maxIter, tol)
%
% Variables de Entrada:
%
% f: vector columna. funcion que rige el sistema de EDO,
%       tiene dos argumentos f(t,x) donde t es vector (s)
%       y x vector columna (sd); t= (t_1,...,t_s); x = (x_1,...,x_s)
%       f = (f(t_1,x_1), ..., f(t_s,x_s))
% df: matriz jacobiana de f para un escalar t y vector u (d)
% N: numero de pasos en los que dividimos el intervalo de
%       integracion
% t0: tiempo inicial
% T: tiempo final
% y0: vector columna, dato inicial
% b,c,A: coeficientes del tablero de BUTCHER.
% A: matriz cuadrada de orden s
% b,c: vectores columna de orden s (b vector de pesos, c vector de nodos)
% maxIter: Número máximo de iteraciones
% tol: tolerancia para las iteraciones
%
% Variables de Salida:
%
% y: matriz de length(u0) x length(t) que contiene la solucion
% t: vector de tiempos
% niter: numero de iteraciones en cada aplicacion de quasi Newton
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [u,t, niter] = RKImplicito_quasiNewton(f,df,N,t0,T,u0,b,c,A, maxIter, tol)
    % Paso equidistante
    h = (T-t0)/N;
    % Vector de tiempos
    t = [t0:h:T];
    % Matriz de la solucion
    d = length(u0);
    u = zeros(d,N+1);
    % Incorporamos el dato inicial en mi solucion numerica
    u(:,1) = u0;
    niter = zeros(N,1);
    s = length(c);
    e = ones(s,1);
    I = eye(d);
    
    % Aplicamos algoritmo de RK-quasiNewton
    for n=1:N
        tt = t(n)+c*h;
        V = kron(e,u(:,n));
        DG = eye(s*d)-h*kron(A,I)*kron(eye(s), df(t(n),u(:,n)));
        IDG = DG\eye(s*d);
        norma = 1;
        while (norma > tol && niter(n) < maxIter)
            niter(n) = niter(n)+1;
            oldV = V;
            G = V - kron(e, u(:,n)) - h*kron(A,I)*f(tt,V);
            V = V - IDG*G;
            norma = norm(V-oldV)/norm(V);
        end
        % avanzamos al siguiente paso
        u(:,n+1) = u(:,n) + h*kron(b',I)*f(tt,V);
    end
end


