%% 
%read data file 
clear;
filename = 'E:\my task.1\matlab_dsp\main\heart_pulse\30_sec.xlsx'; 
%GYRO
PulsesRange = 'A1:A5778';
pulses = xlsread(filename,PulsesRange)';
L=length(pulses);
total_time = 25;     %sec
samples = L;
Ts = total_time / L;
t=(1:L)*Ts;

%% plot pulses signal
figure
plot(t,pulses)
title('pulse 30 sec');

% %
% %% fft for pulses
% Fs=1/Ts;
% % Compute the Fourier transform of the signal.
% Y = fft(pulses);
% % Compute the two-sided spectrum P2. Then compute the single-sided spectrum
% % P1 based on P2 and the even-valued signal length L.
% P2 = abs(Y)/L;
% P1 = P2(1:L/2+1);
% P1(2:end-1) = 2*P1(2:end-1);
% f = Fs*(0:(L/2))/L;
% figure
% plot(f,P1)
% title('Single-Sided Amplitude Spectrum of X(t)')
% xlabel('f (Hz)')
% ylabel('|P1(f)|')
% grid
%% Moving Average Filter
M=30;
h=(1/M)*ones(1,M);

pulses2 = [zeros(1,M-1), pulses, zeros(1,M-1)];
yo  = zeros(1,length(pulses)+M-1);
for i = 1:length(pulses2)- M 
    for j = 1 : M
        yo(i) = yo(i) + h(M+1-j) * pulses2(i+j); 
    end
end

yo=yo(1:length(pulses));
figure
plot(t,pulses,t,yo)
grid

%% pulse rate algorithm
y =yo;
threshold=500;
pks=[]; locs=[]; kp=0;
for k=2:(length(y)-1)
    if ((y(k)>y(k-1)) && (y(k)>y(k+1)))
        if ((y(k)>= threshold) && (k-kp>20))
            pks=[pks y(k)];
            locs=[locs k];
            kp = k;
        end
    end   
end

 %% plote pulse rate 

 figure
 yo =[500*ones(1,50),yo(51:end)]
plot(t,pulses,t,yo)
grid
hold on
plot(t(locs) , pks, 'r', 'Marker', 'v', 'LineStyle', 'none');

title('pulse rate');
xlabel('Time (s)');
ylabel('pulse');
hold off;
%% rate
rate  = (length(pks) / 2) * (60/25)