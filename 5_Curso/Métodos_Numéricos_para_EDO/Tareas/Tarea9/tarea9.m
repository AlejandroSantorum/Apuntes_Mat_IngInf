x = linspace(-10,10,1000);
y = linspace(-10,10,1000);
x_new = [];
y_new = [];
%z = abs((2*complex(x,y) + 6)./((complex(x,y)).^2 -4*complex(x,y) + 6));
for i = 1 :size(x,2)
    for j = 1 :size(y,2)
        if abs((2*complex(x(i),y(j)) + 6))< abs(((complex(x(i),y(j)))^2 -4*complex(x(i),y(j)) + 6)) 
            x_new(end+1) = x(i);
            y_new(end+1) = y(j);
        end
    end
end
plot(x_new,y_new,'o')
