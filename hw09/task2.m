clear; clc;

s = tf('s');
a = s*(s-1);
b = s + 2;
c = (s + 2 + 1i)*(s + 2 - 1i)*(s+2);
f = s^2;

[x1, y1] = axbyc(a, b, c, 'miny')
[x2, y2] = axbyc(f, b, c, 'miny')

%% grafy
% Vyčištění pracovního prostoru
clear; clc; close all;

% 1. Definice přenosové funkce T(s)
% Koeficienty musí být zadány sestupně podle mocniny 's'
num = [0.44, 0.55];               % 0.44s + 0.55
den = [0.11, 0.44, 0.55];         % 0.11s^2 + 0.44s + 0.55
T = tf(num, den);

% 2. Společný časový vektor (od 0 do 4 sekund s krokem 0.01s)
t = 0:0.01:4;

% Vytvoření širokého okna, aby se grafy hezky vešly vedle sebe
figure('Name', 'Odezvy výsledného systému', 'Position', [100, 100, 1000, 400]);

% ==========================================
% GRAF 1: Odezva na rampu
% ==========================================
subplot(1, 2, 1);
u_ramp = t; % Referenční signál typu rampa (y = x)
[y_ramp, t_out] = lsim(T, u_ramp, t); % Simulace lineárního systému (lsim)

% Vykreslení
plot(t_out, y_ramp, 'LineWidth', 1.5); % Odezva (automaticky modrá)
hold on;
plot(t, u_ramp, 'LineWidth', 1.5); % Reference (automaticky oranžová)

% Formátování grafu
grid on;
title('Odezva soustavy na rampu na referenci', 'FontWeight', 'bold');
xlabel('čas [s]');
ylabel('Amplituda');
legend('Odezva', 'Reference', 'Location', 'southeast');
axis([0 4 0 4.5]); % Přesné nastavení os podle zadání

% ==========================================
% GRAF 2: Odezva na jednotkový skok
% ==========================================
subplot(1, 2, 2);
[y_step, t_out] = step(T, t); % Využití vestavěné funkce step()

% Vykreslení
plot(t_out, y_step, 'LineWidth', 1.5);

% Formátování grafu
grid on;
title('Odezva soustavy na jednotkový skok reference', 'FontWeight', 'bold');
xlabel('čas [s]');
ylabel('Amplituda');
axis([0 4 0 1.2]); % Přesné nastavení os podle zadání