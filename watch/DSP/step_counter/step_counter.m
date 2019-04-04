%% 
%read data file 
filename = 'E:\my task.1\matlab_dsp\main\step_counter\maged.xlsx'; 
 
%GYRO
XRange1 = 'B1:B5500';
YRange1 = 'C1:C5500';
ZRange1 = 'D1:D5500';
gyroX = xlsread(filename,XRange1)';
gyroY = xlsread(filename,YRange1)';
gyroZ = xlsread(filename,ZRange1)';

%ACCEL
XRange1 = 'F1:F5500';
YRange1 = 'G1:G5500';
ZRange1 = 'H1:H5500';
accX = xlsread(filename,XRange1)';
accY = xlsread(filename,YRange1)';
accZ = xlsread(filename,ZRange1)';

Ts=0.01;
L=length(accX);
t=(1:L)*Ts;

%% plot gyro an acc in x,y,z

% %figue gyrox
% figure
% plot(t,gyroX)
% title('gyro X');

% %figue gyroy
% figure
% plot(t,gyroY)
% title('gyro Y');

% %figue gyroZ
% figure
% plot(t,gyroZ)
% title('gyro Z');

% %figue accx
% figure
% plot(t,accX)
% title('accel X');

% %figue accy
% figure
% plot(t,accY)
% title('accel Y');

% %figue accx
% figure
% plot(t,accZ)
% title('accel Z');

%%
Fs=1/Ts;
% Compute the Fourier transform of the signal.
Y = fft(gyroY);
% Compute the two-sided spectrum P2. Then compute the single-sided spectrum
% P1 based on P2 and the even-valued signal length L.
P2 = abs(Y)/L;
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = Fs*(0:(L/2))/L;
figure
plot(f,P1)
title('Single-Sided Amplitude Spectrum of X(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')
grid
%%
% Moving Average Filter
M=30;
h=(1/M)*ones(1,M);

%y1=conv(gyroX,h);           %threshold for  x =2/3 of y or z
y1=conv(gyroY,h);
%y1=conv(gyroZ,h);


gY = [zeros(1,M-1), gyroY, zeros(1,M-1)];
yo  = zeros(1,length(gyroY)+M-1);
for i = 1:length(gY)- M 
    for j = 1 : M
        yo(i) = yo(i) + h(M+1-j) * gY(i+j); 
    end
end
y=y1(1:length(gyroY));

yo=yo(1:length(gyroY));
% y=conv(x,h,'same');
figure
plot(t,gyroY,t,yo)
grid
%% step counter algorithm
threshold=30;
pks=[]; locs=[]; kp=0;

for k=2:(length(y)-1)
    if (y(k)>y(k-1)) && (y(k)>y(k+1))
        if (y(k)>= threshold) && (k-kp>40)
            pks=[pks y(k)];
            locs=[locs k];
            kp = k;
        end
    end   
end
 %% plote steps magnitude 
hold on;
plot(t(locs-1) , pks, 'r', 'Marker', 'v', 'LineStyle', 'none');
title('Counting Steps');
xlabel('Time (s)');
ylabel('Acceleration Magnitude, No Gravity (m/s^2)');
hold off;

length(pks)