function [r, ERR] = funcion1(x, n)

    %x = pi / 10;

    %n = 10;

    r = 0;

    for k=0:n
        r = r + (x^k/factorial(k));
    end

    ERR = exp(x) - r;

end
