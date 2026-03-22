% 1. Definice komplexní proměnné 's'
s = tf('s');

% 2. Zadání přenosu řízené soustavy P(s)
P = (s+2)/(s^2 - 1);
C_new = (s+1)/s;

% 3. Spuštění nástroje pro návrh metodou Root Locus
%rltool(P);

% Vytvoření uzavřené smyčky (soustava * regulátor, zpětná vazba = 1)
T = feedback(P * C, 1);

% Pokrácení zlomku do základního tvaru (jako v rovnici 19)
T_vysledny = minreal(T)