%3
figure
w0=[pi/8, pi/4, pi/2, pi, 5*pi/4, 3*pi/2, 2*pi];
n=-5:0.1:15;
for i = 1:7
    subplot(3,3,i);
    points = sin(w0(i).*n);
    plot(points);
end
title('3')