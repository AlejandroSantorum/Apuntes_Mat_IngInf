function [Im,It,Is,I2,I3] = integracion(f,a)

x  = 0; w = 2;
Im = Icompab(f,a,w,x);

x  = [-1,1]; w = [1,1];
It = Icompab(f,a,w,x);

Is = It/3 + 2*Im/3;

x  = [-1/sqrt(3),1/sqrt(3)]; w = [1,1];
I2 = Icompab(f,a,w,x);

x  = [-sqrt(3/5),0,sqrt(3/5)]; w = [5,8,5]/9;
I3 = Icompab(f,a,w,x);

end