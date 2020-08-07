function [der] = d(f, x0, h)
    
    temp = x0 + h;
    h = temp - x0;  % elimina la propagación de los errores debidos
                    % a la no exacta representación de h a la hora de 
                    % evaluar en f
                    
    der = ((f(x0+h) - f(x0-h))./(2*h));
   
end