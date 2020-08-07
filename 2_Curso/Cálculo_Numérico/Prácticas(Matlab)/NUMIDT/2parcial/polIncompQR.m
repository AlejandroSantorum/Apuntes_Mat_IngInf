function [coeficientes] = polIncompQR(b, nodos, m)
% b es un vector de mediciones: puede ser f(nodos) o
% unas mediciones mas inexactas y este codigo el busca
% el polinomio mas parecido a esos puntos
   if size(b,2) > size(b,1); b = b'; end
    n = length(b);
    V(:,1) = ones(n,1);
    for k = 2:m
        V(:,k) = nodos.^(k-1);
    end
    coeficientes = solveIncompQR(V , b);

    x = min(nodos):(max(nodos)-min(nodos))/1000:max(nodos);
    for i = 1:length(x)
        p(i) = 0;
        for k = 1:m
            p(i) = p(i) + coeficientes(k)*x(i)^(k-1);
        end
    end

    figure
    plot(nodos, b, '*r')
    hold on
    plot(x,p)
end
