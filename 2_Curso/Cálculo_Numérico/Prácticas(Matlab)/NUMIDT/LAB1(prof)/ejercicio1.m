N = 12;

% E = zeros(N,1);

% for n=1:N
%    
%     [~,E(n)] = mixmix(pi/10,n);
%     
% end


[~,E] = mixmix(pi/10,N);

plot(1:N+1,E)