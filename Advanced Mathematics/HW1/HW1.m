syms k x;
x = (-10:.1:10);

%K = 1
S1 = pi/2 - symsum((cos(((2*k)-1)*x)*(4/(((2*k)-1)^2)*pi)), k, 1, 1);
plot(x, S1);
xlabel('x');
ylabel('f(x)');
title('K = 1')

%K = 5
S5 = pi/2 - symsum((cos(((2*k)-1)*x)*(4/(((2*k)-1)^2)*pi)), k, 1, 5);
plot(x, S5);
xlabel('x');
ylabel('f(x)');
title('K = 5')

%K = 20
S20 = pi/2 - symsum((cos(((2*k)-1)*x)*(4/(((2*k)-1)^2)*pi)), k, 1, 20);
plot(x, S20);
xlabel('x');
ylabel('f(x)');
title('K = 20')

%K = 100
S100 = pi/2 - symsum((cos(((2*k)-1)*x)*(4/(((2*k)-1)^2)*pi)), k, 1, 100);
plot(x, S100);
xlabel('x');
ylabel('f(x)');
title('K = 100')
