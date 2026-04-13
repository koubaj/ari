clear; clc;

% 1. Definice symbolických proměnných
syms K1 K2 K3 KI

% 2. Definice matic jako symbolických výrazů
% Funkce sym() převede desetinná čísla z vašeho zadání na exaktní zlomky.
% Díky tomu získáte přesně ty stejné tvary, které máte v PDF.
A = sym([-0.04167, 0, -0.0058;
          0.0217, -0.24, 0.0058;
          0, 100, -2.4]);
B = sym([5.2; -5.2; 0]);
C = sym([0, 0, 1]);

K = [K1, K2, K3];

% 3. Sestavení celkové matice
A_celk = [A - B*K, B*KI;
         -C,       0];

% 4. Výpočet symbolického charakteristického polynomu
% charpoly() vypočítá det(sI - A_celk) a vrátí vektor koeficientů
% Vektor je seřazený od s^4 po s^0: [1, a3, a2, a1, a0]
coefs = charpoly(A_celk);

% 5. Extrakce a výpis jednotlivých koeficientů (odpovídá rovnici 7)
fprintf('--- Symbolické rovnice koeficientů (Rovnice 7) ---\n\n');

disp('a3 (u s^3) =');
disp(coefs(2))

disp('a2 (u s^2) =');
disp(coefs(3))

disp('a1 (u s^1) =');
disp(coefs(4))

disp('a0 (absolutní člen u s^0) =');
disp(coefs(5))