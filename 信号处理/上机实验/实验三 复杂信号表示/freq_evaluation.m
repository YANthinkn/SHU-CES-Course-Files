% This function is used for frequency domain evaluation for a given signal,
% based on FFT, and gives a spectrum plot.
% input :
% x: the input signal (N*1 or 1*N)
% F_sample: your sampling frequency
function freq_evaluation(x, F_sample)
L = 8000;
y=fft(x, L);
P2 = abs(y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = F_sample*(0:L/2)/L;
plot(f,P1);
title('Single-Sided Amplitude Spectrum of X(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')
end

