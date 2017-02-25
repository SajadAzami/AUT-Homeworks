%1
figure
t = -1:0.1:10;
plot(t, 3 * (exp(-2 * t).^heaviside(t)));
title('1.1')

%2
figure
plot(t, sin(2 * t) + 2 * cos(3 * t - 0.2));
title('1.2')

%3
figure
plot(t, (exp(-2 * t).^sin(3 * t)).^heaviside(t));
title('1.3')

%4
figure
plot(t, (exp(-t).^heaviside(t)) + (exp(-t).^(exp(2*t - 4) - 1).^heaviside(t - 2)) - exp(t - 4).^heaviside(t - 4));
title('1.4')
