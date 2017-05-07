clear;

% Q.1.A
Fs = 100;           % Sampling frequency
t = (-1/2:1/Fs:1/2);% Time vector 
x = t./t;
x(isnan(x)) = [1]
L = length(t);      % Signal length


n = 2^nextpow2(L);
Y = fft(x,n);
f = Fs*(0:(n/2))/n;
P = abs(Y/n);
figure
plot(f,P(1:n/2+1))

% Q.1.B
Fs = 100;           % Sampling frequency
t = -1:1/Fs:1;      % Time vector 
L = length(t);      % Signal length
x = -abs(abs(t-1)-1);
figure
plot(t,x)

n = 2^nextpow2(L);
Y = fft(x,n);
f = Fs*(0:(n/2))/n;
P = abs(Y/n);
figure
plot(f,P(1:n/2+1)) 
title('Delta in Frequency Domain')
xlabel('Frequency (f)')

%-------------------------------------------------
% Q.2.A
Fs = 1000;                    % Sampling frequency
T = 1/Fs;                     % Sampling period
t = (-5:0.1:5);              % Time vector
L = length(t);                % Signal length

x = sin(pi*t)./t;
x(isnan(x))=0

figure
plot(t,x)
title('Sin(t)/t in Time Domain')
xlabel('Time (t)')

n = 2^nextpow2(L);
Y = fft(x, n);
f = Fs*(0:(n/2))/n;
P = abs(Y/n);
figure
plot(f,P(1:n/2+1)) 
title('Sin(t)/t in Frequency Domain')
xlabel('Frequency (f)')


% Q.2.B
Fs = 1000;                    % Sampling frequency
T = 1/Fs;                     % Sampling period
t = (-5:0.1:5);              % Time vector
L = length(t);                % Signal length

x = 1+exp(-t.^2);
x(isnan(x))=0

figure
plot(t,x)
title('1+exp(-t^2) in Time Domain')
xlabel('Time (t)')

n = 2^nextpow2(L);
Y = fft(x, n);
f = Fs*(0:(n/2))/n;
P = abs(Y/n);
figure
plot(f,P(1:n/2+1)) 
title('1+exp(-t^2) in Frequency Domain')
xlabel('Frequency (f)')


%-------------------------------------------------
% Q.3.A
w = (-5:0.1:5);               % Frequency vector

x = exp(-w.^2);
Y = ifft(x);
plot(w, Y) 
title('exp(-w^2) in Time Domain')
xlabel('Time (t)')

% Q.3.B
t = (-5:0.1:5);               % Time vector
x = t;
Y = ifft(x);
figure
plot(t,Y) 
title('Time Domain')
xlabel('Time(t)')


