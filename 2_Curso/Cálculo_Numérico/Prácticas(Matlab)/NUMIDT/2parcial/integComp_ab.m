function [sumat] = integComp_ab(f, a, w, x)
    if(length(x) ~= length(w))
       error('tamaño del vector de pesos W distinto al vector de nodos X'); 
    end
    
    tam = length(a);
    sumat = 0;
    
    for k = 1:tam-1
        sumat = sumat + integSimple_ab(f, a(k), a(k+1), w, x);
    end


end