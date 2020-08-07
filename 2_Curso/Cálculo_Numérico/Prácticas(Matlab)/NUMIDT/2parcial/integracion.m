function [medio, trapecio, simpson, gauss2, gauss3] = integracion(f, a)
    
    medio = integComp_ab(f, a, 2, 0);
    trapecio = integComp_ab(f, a, [1,1], [1, -1]);
    simpson = integComp_ab(f, a, [1/3, 4/3, 1/3], [-1, 0, 1]);
    gauss2 = integComp_ab(f, a, [1, 1], [1/sqrt(3), -1/sqrt(3)]);
    gauss3 = integComp_ab(f, a, [5/9, 8/9, 5/9], [-sqrt(3/5), 0, sqrt(3/5)]);
    
end