close all;
T = 1/5000;
M=64;
Te = 1/(320*10^3);
Fe = 1/Te;
Tsim = T-Te; 
 
Res=sim('simulinkLaser');
plot(Res.laser);

res = fft(Res.laser.Data, M)/M;
x = linspace(0, M-1, M)
f = x / (M*Te);
figure
semilogy(f,abs(res));
figure
H = tf([1], [1.7483*10^-23 7.6663*10^-18 1.162*10^-11 3.0332*10^-6 1]);
bode(H);