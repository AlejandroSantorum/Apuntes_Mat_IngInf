clear; clc;

%f = @(x) x.^5 + 37*x.^2 - 12;
f = @(x) 1./(1+x.^2);


a = -5;  b= 5;

TOP = 50;

for N = 2:TOP
    v = a:(b-a)/(N-1):b; % Nodos equiespaciados entre a y b
    
    [medio(N), trapecio(N), simpson(N), gauss2(N), gauss3(N)] = integracion(f, v);
end

figure
subplot(2, 2, 1); plot(2:TOP, medio(2:TOP))
subplot(2, 2, 2); plot(2:TOP, simpson(2:TOP))
subplot(2, 2, 3); plot(2:TOP, gauss2(2:TOP))
subplot(2, 2, 4); plot(2:TOP, gauss3(2:TOP))

I = gauss3(TOP);

medio(2:TOP) = abs(medio(2:TOP) - I);
trapecio(2:TOP) = abs(trapecio(2:TOP) - I);
simpson(2:TOP) = abs(simpson(2:TOP) - I);
gauss2(2:TOP) = abs(gauss2(2:TOP) - I);
gauss3(2:TOP) = abs(gauss3(2:TOP) - I);

figure
subplot(2,2,1); plot(2:TOP, log10(medio(2:TOP)))
subplot(2,2,2); plot(2:TOP, log10(simpson(2:TOP)))
subplot(2,2,3); plot(2:TOP, log10(gauss2(2:TOP)))
subplot(2,2,4); plot(2:TOP, log10(gauss3(2:TOP)))