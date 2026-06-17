% =========================================================================
% UKÁZKA: Simulace regulačního obvodu v MATLABu
% Příklad: Dvojitý integrátor a PD regulátor
% =========================================================================
clear; clc; close all;

%% 1. Definice Laplaceova operátoru 's'
% Tohle je nejlepší trik - odteď můžeme psát přenosy úplně přirozeně
s = tf('s');

%% 2. Definice přenosů (Soustava a Regulátor)
% Soustava: Dvojitý integrátor
G = 1 / s^2; 

% Regulátor: Náš PD regulátor z kuchařky (Kp = 4, Kd = 4)
C = 4 + 4*s; 

% Tip: Zkuste si sem zkusmo napsat čistý P-regulátor (např. C = 4;) 
% a uvidíte, jak se grafy zblázní a začnou trvale kmitat!

%% 3. Spojení bloků do uzavřené smyčky
% Funkce feedback(prima_vetev, zpetna_vetev) automaticky spočítá jmenovatele 1+CG.

% A) Přenos z reference na VÝSTUP (jak se hýbe samotný stroj)
% Přímá větev je C*G, zpětná vazba je 1 (drát od senzoru zpět)
T_y = feedback(C * G, 1);

% B) Přenos z reference na AKČNÍ ZÁSAH (co posílá regulátor do stroje)
% Přímá větev je pouze C, zpětná vazba jde "přes" systém G
T_u = feedback(C, G);

%% 4. Vykreslení výsledků (Přechodové charakteristiky)
% Vygenerujeme časový vektor např. na 5 sekund, aby byly grafy hezké
t = 0:0.01:5; 

figure('Name', 'Analýza PD regulátoru na dvojitém integrátoru');

% Horní graf: Chování výstupu y(t)
subplot(2, 1, 1);
step(T_y, t);
title('Odezva systému na skok žádané hodnoty (Výstup y)');
ylabel('Poloha / Výstup');
grid on;
% (Můžete použít i příkaz stepinfo(T_y) pro výpis překmitu a doby ustálení)

% Dolní graf: Úsilí regulátoru u(t)
subplot(2, 1, 2);
step(T_u, t);
title('Akční zásah regulátoru (Signál u)');
ylabel('Výkon / Napětí');
xlabel('Čas [s]');
grid on;