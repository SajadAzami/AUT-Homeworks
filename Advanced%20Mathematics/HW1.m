syms k x;
x = [0:.1:100];
S2 = symsum(pi/2 - (cos((2*k-1)*x)*(4/((2*k-1)^2)*pi)), k, 1, 5);
plot(S2);