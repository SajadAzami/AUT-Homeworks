n=-10:0.1:10;

%4.1
figure
plot((0.7.^n).*sin(pi.*n./4)-cos(pi.*n./4));
title('4.1')

%4.2
figure
plot(cos((n.^2).*pi./4));
title('4.2')

%4.3
figure
plot(3.*heaviside(n-2)+2.*heaviside(-n-2)+(1-exp(0.2.*n)).*heaviside(-n+1));
title('4.3')