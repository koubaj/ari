% =========================================================
% ŘEŠENÍ ÚKOLU 2 V MATLABU
% =========================================================
clear; clc;

%% Část A a B: Nelineární model a Linearizace
disp('--- Bod a) a b): Linearizace nelineárního systému ---');

% 1. Definice symbolických proměnných (vyžaduje Symbolic Math Toolbox)
syms x1 x2 u

% 2. Zápis nelineárních diferenciálních rovnic získaných ze schématu
% (tyto rovnice jsme odvodili ze Simulinkového schématu)
f1 = -x1 - 3*x2 + 2*u;
f2 = -3*x1*u;

% Vytvoření vektoru stavových derivací f(x,u) a vektoru stavů x
f = [f1; f2];
x = [x1; x2];

% 3. Výpočet Jakobiánů SYMBOLICKY (matice parciálních derivací)
A_sym = jacobian(f, x); % Derivace f podle [x1, x2]
B_sym = jacobian(f, u); % Derivace f podle u

disp('Symbolická matice A:');
disp(A_sym);

% 4. Dosazení pracovního (rovnovážného) bodu
x1_0 = 1;
x2_0 = 1;
u_0  = 0;

% Subs nahradí symbolické proměnné za čísla, double to převede na číselnou matici
A_lin = double(subs(A_sym, [x1, x2, u], [x1_0, x2_0, u_0]));
B_lin = double(subs(B_sym, [x1, x2, u], [x1_0, x2_0, u_0]));

disp('Linearizovaná matice A_lin pro zadaný pracovní bod:');
disp(A_lin);
disp('Linearizovaná matice B_lin pro zadaný pracovní bod:');
disp(B_lin);

%% Část C: Návrh stavové zpětné vazby
disp('--- Bod c): Návrh matice K ---');

% 1. Definice požadovaného charakteristického polynomu
% Zadaný polynom: s^2 + 18s + 9
% V MATLABu zadáváme polynomy jako vektory jejich koeficientů (od nejvyšší mocniny s)
poly_req = [1, 18, 9];

% 2. Získání požadovaných pólů systému (kořeny zadaného polynomu)
poles_req = roots(poly_req);

disp('Požadované póly uzavřené smyčky (z polynomu):');
disp(poles_req);

% 3. Výpočet matice zpětné vazby K
% Funkce 'acker' používá Ackermannův vzorec pro SISO systémy (1 vstup).
% (Alternativou je funkce 'place', která funguje i pro MIMO systémy).
K = acker(A_lin, B_lin, poles_req);

disp('Výsledná matice stavové zpětné vazby K:');
disp(K);

% Volitelné ověření, zda matice (A - B*K) má opravdu správný polynom:
A_reg = A_lin - B_lin * K;
poly_check = poly(A_reg); % Vypočítá koeficienty polynomu z matice
disp('Ověření - polynom matice (A - B*K):');
disp(poly_check);