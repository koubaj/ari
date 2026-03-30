% 1. Zadej sva cisla
a = 1; 
b = 5;

% Definice symbolickych promennych
syms s Kp Ki Kd

% 2. Sestaveni rovnic
% Jmenovatel prenosu systemu s PID (skutecny)
Pc = s*(s^2 + b) + (s + a)*(Kd*s^2 + Kp*s + Ki);
Pc = collect(Pc, s); % Seskupi k sobe cleny se stejnou mocninou 's'

% Zadani pozadovanych polu a sestaveni idealniho polynomu
p1 = -1; p2 = -0.5 + 0.5i; p3 = -0.5 - 0.5i;
Pd = (s - p1)*(s - p2)*(s - p3);
Pd = expand(Pd);

% Srovnani bazi (vynasobime idealni polynom clenem u s^3 ze skutecneho polynomu)
% Z 'Pc' vime, ze koeficient u s^3 je (1+Kd).
Pd_scaled = expand(Pd * (1 + Kd));

% Extrahujeme koeficienty obou polynomu
coeffs_Pc = coeffs(Pc, s);
coeffs_Pd = coeffs(Pd_scaled, s);

% Sestavime soustavu rovnic (porovnavame koeficienty u s^0, s^1, s^2)
eq1 = coeffs_Pc(1) == coeffs_Pd(1);
eq2 = coeffs_Pc(2) == coeffs_Pd(2);
eq3 = coeffs_Pc(3) == coeffs_Pd(3);

% 3. Vypocet
reseni = solve([eq1, eq2, eq3], [Kp, Ki, Kd]);

% Vypis vysledku jako desetinná čísla
Kp_vysledek = double(reseni.Kp)
Ki_vysledek = double(reseni.Ki)
Kd_vysledek = double(reseni.Kd)

% 4. OVERENI VYSLEDKU
C = pid(Kp_vysledek, Ki_vysledek, Kd_vysledek);
F = tf([1 a], [1 0 b]);
Uzavreny_obvod = feedback(C*F, 1);
disp('Skutecne poly systemu jsou:');
pole(Uzavreny_obvod) % Melo by vypsat presne -1, a -0.5 +- 0.5i