%1.1
figure
t = -1:0.1:10;
plot(3 * (exp(-2 .* t).*heaviside(t)));
title('1.1')

%1.2
figure
plot(sin(2 * t) + 2 * cos(3 * t - 0.2));
title('1.2')

%1.3
figure
plot(exp(-2 * t).*sin(3 * t).*heaviside(t));
title('1.3')

%1.4
figure
plot(exp(-t).*heaviside(t) + (exp(-t).*(exp(2*t - 4) - 1).*heaviside(t - 2)) - exp(t - 4).*heaviside(t - 4));
title('1.4')
