
%read data file 
filename = 'E:\my task.1\matlab_dsp\maged.xlsx';
filter_size=20;

%GYRO
XRange1 = 'B1000:B2000';
YRange1 = 'C1000:C2000';
ZRange1 = 'D1000:D2000';
gyroX = xlsread(filename,XRange1)';
gyroY = xlsread(filename,YRange1)';
gyroZ = xlsread(filename,ZRange1)';


%ACCEL
XRange1 = 'F1000:F2000';
YRange1 = 'G1000:G2000';
ZRange1 = 'H1000:H2000';
accX = xlsread(filename,XRange1)';
accY = xlsread(filename,YRange1)';
accZ = xlsread(filename,ZRange1)';


Ts=0.01;
L=length(accX);
t=(1:L)*Ts;
x=zeros(1,L);
gyroX_F=zeros(1,L);
gyroY_F=zeros(1,L);
gyroZ_F=zeros(1,L);
sum_F_F=zeros(1,L);
% % 
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
% %
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
% 

%% gyroX_F
%Hanning Recursive Smoothing Technique
for n = filter_size+1: L
    
    for i = 1:filter_size
    gyroX_F(n) = gyroX_F(n)+gyroX(n-i);
    end
gyroX_F(n)=gyroX_F(n)/filter_size;
end
%%

 plot(t,gyroX,'r')
hold on
 plot(t,gyroX_F);
 
%% gyroY_F
%Hanning Recursive Smoothing Technique
for n = filter_size+1: L
    
    for i = 1:filter_size
    gyroY_F(n) = gyroY_F(n)+gyroY(n-i);
    end
gyroY_F(n)=gyroY_F(n)/filter_size;
end
%%
figure
 plot(t,gyroY,'r')
hold on
 plot(t,gyroY_F);
 
%% gyroZ_F
%Hanning Recursive Smoothing Technique
for n = filter_size+1: L    
    for i = 1:filter_size
    gyroZ_F(n) = gyroZ_F(n) + gyroZ(n-i);
    end
gyroZ_F(n)=gyroZ_F(n)/filter_size;
end

%%
figure
 plot(t,gyroZ,'r')
hold on
 plot(t,gyroZ_F);
%% sum_F                            /// FITER - SUM - FILTER
%

sum=gyroX+gyroY+gyroZ;
sum_F=gyroX_F+gyroY_F+gyroZ_F;
figure
 plot(t,sum,'r')
hold on
 plot(t,sum_F);
 
%% sum_F_F                    
%Hanning Recursive Smoothing Technique
for n = filter_size+1: L
    for i = 1:filter_size
    sum_F_F(n) = sum_F_F(n)+sum_F(n-i);
    end
sum_F_F(n)=sum_F_F(n)/filter_size;
end



figure
 plot(t,sum,'r')
hold on
 plot(t,sum_F,'g');
hold on
 plot(t,sum_F_F);
 
  %% sum                         ///  SUM - FILTER - filter
%
sum=gyroX+gyroY+gyroZ;
%% sum_F                 
%Hanning Recursive Smoothing Technique
for n = filter_size+1: L
    for i = 1:filter_size
    sum_F(n) = sum_F(n)+sum(n-i);
    end
sum_F(n)=sum_F(n)/filter_size;
end

%% sum_F_F                 
%Hanning Recursive Smoothing Technique
for n = filter_size+1: L
    for i = 1:filter_size
    sum_F_F(n) = sum_F_F(n)+sum_F(n-i);
    end
sum_F_F(n)=sum_F_F(n)/filter_size;
end

figure
 plot(t,sum,'r')
hold on
 plot(t,sum_F,'g');
hold on
 plot(t,sum_F_F);
 
 %% cross corolation
 %
 
 