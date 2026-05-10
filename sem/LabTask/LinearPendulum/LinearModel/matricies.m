% pracovni bod 0 0 0 3*pi/2:
% stavy: v, x, w, phi

A = [-4.979 0 0.036 3.01;
    1 0 0 0;
    50.688 0 -1.522 -125.838;
    0 0 1 0];

B = [8.584
    0
    -87.394
    0];

C = [0 1 0 0
     0 0 0 1];
 D = 0;
 
 G = eye(size(A,1));
H = zeros(size(C,1),size(A,1));
Ts = 0.005;
sysd = c2d(ss(A, B, C, D), Ts);
sys = ss(sysd.A, [sysd.B, G], sysd.C, [sysd.D, H], Ts, 'inputname', 'u', 'outputname', 'y');

Q = eye(size(A,1));

R = eye(size(C,1));

[kalmf,L,P] = kalman(sys,Q,R,zeros(size(A,1),size(C,1)));

% vstupni saturace vsechno +-1, mrtve pasmo +-0.11
% saturace polohy +-0.35