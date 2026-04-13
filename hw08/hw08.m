clear; clc;

%% 1. Definice původního systému
A = [-0.04167, 0, -0.0058;
      0.0217, -0.24, 0.0058;
      0, 100, -2.4];
B = [5.2; -5.2; 0];
C = [0, 0, 1];
D = 0;
sys = ss(A, B, C, D);

%% 2. Výpočet požadovaných pólů uzavřené smyčky
% a) Dominantní póly ze specifikace
OS = 0.10; % OPRAVA: 10 % je 0.10
Ts = 100;
zeta = -log(OS) / sqrt(pi^2 + log(OS)^2);
wn = 4 / (zeta * Ts);
p1 = -zeta*wn + 1i * wn * sqrt(1 - zeta^2);
p2 = -zeta*wn - 1i * wn * sqrt(1 - zeta^2);

s = tf('s');
char_poly = s^2 + 2*wn*zeta*s + wn^2;

% b) Pól pro vykrácení nuly (podle nápovědy v zadání)
z_sys = zero(sys); % Najde nulu původního systému
p3 = z_sys(1);     % Umístíme 3. pól přesně na hodnotu nuly (cca -0.1302)

% c) Čtvrtý pól (rychlý, aby neovlivnil dynamiku)
p4 = -100;

% Vektor všech požadovaných pólů
p_req = [p1; p2; p3; p4];

%% 3. Návrh integrálního řízení pomocí rozšířeného systému
% Vytvoření matic rozšířeného systému (Augmented system)
A_aug = [A, zeros(3,1); 
        -C, 0];
B_aug = [B; 0];

% Výpočet zisků stavové zpětné vazby pomocí funkce place
% TOTO nahrazuje to složité řešení soustavy rovnic!
K_aug = place(A_aug, B_aug, p_req);

% Extrakce K a KI (pozor na znaménko u KI vzhledem k vaší matici A_celk)
K = K_aug(1:3);
KI = -K_aug(4);

fprintf('--- Vypočtené zisky ---\n');
fprintf('K = [%.4f, %.4f, %.4f]\n', K(1), K(2), K(3));
fprintf('KI = %.4f\n\n', KI);

%% 4. Sestavení výsledného uzavřeného systému a simulace
% Použijeme vaši strukturu matic
A_celk = [A - B*K,  B*KI;
         -C,        0];
B_celk = [0; 0; 0; 1];
C_celk = [C, 0];
D_celk = 0;

sys_celk = ss(A_celk, B_celk, C_celk, D_celk);

% Vykreslení přechodové charakteristiky
figure;
step(sys_celk);
title('Odezva uzavřeného systému na jednotkový skok');
xlabel('Čas [dny]');
ylabel('Počet volných částic viru');
grid on;

% Výpis parametrů odezvy pro kontrolu zadání
info = stepinfo(sys_celk)

%% 5. Výpis charakteristického polynomu
% Získání vektoru koeficientů z celkové matice A
coefs = poly(A_celk);

% Vytvoření proměnné 's' pro hezký textový výpis
s = tf('s');

% Sestavení a výpis charakteristického polynomu 4. řádu
fprintf('\nCharakteristický polynom uzavřeného systému:\n');
char_poly_uzavreny = coefs(1)*s^4 + coefs(2)*s^3 + coefs(3)*s^2 + coefs(4)*s + coefs(5)

% Pro jistotu si můžeme vypsat i kořeny tohoto polynomu 
% (musí se přesně shodovat s naším vektorem p_req)
fprintf('Kořeny polynomu (póly uzavřené smyčky):\n');
poly_ = roots(coefs)