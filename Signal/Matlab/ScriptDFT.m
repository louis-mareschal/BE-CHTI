close all;
Fsin = 64;
T = 1/Fsin;
M=32;
Te = T/M;
Fe = 1/Te;
Tsim = T-Te; 
 
Res=sim('SimulinkDFT');
plot(Res.Sinus_Continu);
hold on; % permet de superposer la courbe à suivre
plot(Res.Sinus_Echanti,'o');

% Q7
res = fft(Res.Sinus_Echanti.Data, M)/M;
%x = linspace(0, M-1, M)
f = x / (M*Te);
figure
plot(f,abs(res));
