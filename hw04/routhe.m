clear; clc;

syms kp ki

a0=1; a1=3;
a2=kp+2; a3=ki;
a4=0; a5=0;

b3=0;

b1=-det([a0 a2; a1 a3])/a1;
b2=-det([a0 a4; a1 a5])/a1;
c1=simplify(-det([a1 a3; b1 b2])/b1);
c2=-det([a1 a5; b1 b3])/b1;

%% graf
% Podmínky
cond1 = ki > 0;
cond2 = kp > (1/3)*ki - 2;

% Vykreslení pomocí fplot a vyplnění oblasti
figure;
hold on;

% Definice rozsahu pro osu x (ki)
ki_vals = linspace(0, 15, 400); 
% Mezní přímka: kp = 1/3 * ki - 2
kp_boundary = (1/3)*ki_vals - 2;

% Vyplnění oblasti (stínování)
% Nastavíme horní limit grafu pro vizualizaci, např. 10
fill([ki_vals, fliplr(ki_vals)], [kp_boundary, ones(size(ki_vals))*10], ...
    [0.8 0.9 1], 'EdgeColor', 'none', 'DisplayName', 'Oblast stability');

% Vykreslení hraničních čar
plot(ki_vals, kp_boundary, 'r', 'LineWidth', 2, 'DisplayName', 'kp = 1/3*ki - 2');
xline(0, 'k--', 'LineWidth', 2, 'DisplayName', 'ki = 0');

% Formátování grafu
grid on;
xlabel('k_i');
ylabel('k_p');
title('Oblast parametrů vyhovující podmínkám');
legend('Location', 'northwest');
axis([0 15 -3 10]); % Nastavení mezí zobrazení
hold off;