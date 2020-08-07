function[ljVector] = Lj(Xvector, a)
    [row, col] = size(Xvector);
    if row ~= 1 && col ~= 1
        error('dimensión Xvector incorrecta');
    end
    
    n = length(Xvector);
    ljVector = ones(n,1);
    
    for j = 1:n
        for k = 1:n
            if j ~= k
                ljVector(j) = ljVector(j) * ((a-Xvector(k))/(Xvector(j) - Xvector(k)));
            end
        end
    end
end