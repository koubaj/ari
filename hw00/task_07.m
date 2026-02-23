s = tf('s');
G_s = (s-3) / ((s+1)*(s+7));

Ts_right = 0.01;
Ts_wrong = 1;

G_z_right = c2d(G_s, Ts_right, 'zoh');
G_z_wrong = c2d(G_s, Ts_wrong, 'zoh');

disp('Spojitý přenos:'); G_s;
disp('Diskrétní přenos (vhodná Ts):'); G_z_right;
disp('Diskrétní přenos (nevhodná Ts):'); G_z_wrong;

% --- 1. GRAF: Vhodná perioda vzorkování ---
figure;
% Spojitý systém vykreslíme klasicky
plot(out.simout.Time, out.simout.Data(:, 1), 'b', 'LineWidth', 1.5); 
hold on;
% Diskrétní systém vykreslíme jako SCHODY
stairs(out.simout.Time, out.simout.Data(:, 2), 'r', 'LineWidth', 1.5);
hold off;

grid on;
title('Porovnání: Spojitý vs. Diskrétní (Vhodná Ts)');
xlabel('Čas [s]');
ylabel('Amplituda [-]');
% Legenda nyní dynamicky načte správnou hodnotu Ts
legend('Spojitý', ['Diskrétní T = ', num2str(Ts_right), ' s'], 'Location', 'best');


% --- 2. GRAF: Nevhodná perioda vzorkování ---
figure;
plot(out.simout.Time, out.simout.Data(:, 1), 'b', 'LineWidth', 1.5); 
hold on;
stairs(out.simout.Time, out.simout.Data(:, 3), 'y', 'LineWidth', 1.5);
hold off;

grid on;
title('Porovnání: Spojitý vs. Diskrétní (Nevhodná Ts)');
xlabel('Čas [s]');
ylabel('Amplituda [-]');
legend('Spojitý', ['Diskrétní T = ', num2str(Ts_wrong), ' s'], 'Location', 'best');