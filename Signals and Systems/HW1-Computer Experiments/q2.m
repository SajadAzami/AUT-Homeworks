%2.1
figure
t1 = 0:0.1:pi/2;
t2 = pi/2:0.1:2*pi;
t3 = 2*pi:0.1:10;
points1 = zeros(1,16);
points3 = ones(1,38);
points2 =  sin(t2);
points = cat(2, points1, points2, points3);
t = cat(2, t1, t2, t3);
plot(points);
title('2.1')

%2.2
figure
t = -0.4:0.01:0.4;
plot((sin(pi * t).*cos(pi * t / 2)) ./ (pi * t).*(1 - t.^2));
title('2.2')
