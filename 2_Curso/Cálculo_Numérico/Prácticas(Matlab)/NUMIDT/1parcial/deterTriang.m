function [d] = deterTriang(A)
    n = length(A);
    d = 1;
    for i = 1:n
        d = d * A(i,i);
    end
end