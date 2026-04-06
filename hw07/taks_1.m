s = tf('s');
M = 1/ (s*(s+50)*(s+100));

omega_pm = 25.86;

figure;
bode(M);
grid on;

[mag, phase] = bode(M, omega_pm);

% 4. Spočítáme K jako převrácenou hodnotu
K = 1 / mag;

L = K * M;
T = feedback(L, 1);

% 4. Vykreslení odezvy na skok
figure;
step(T);
grid on;