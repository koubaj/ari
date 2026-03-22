% 1. Definice přenosu soustavy
s = tf('s');
G = 1 / ((s+9)*(s+54));

% 2. Výpočet ideální polohy nuly regulátoru
% Zrušíme pomalejší pól soustavy umístěním nuly na z = 9
z = 9; 

% Po zrušení (s+9) se systém chová jako L(s) = K_p / (s*(s+54))
% Větve Root Locus se setkají v polovině mezi 0 a -54, což je -27.
% Reálná část dominantních pólů tedy bude přesně -27.
re = 27; % absolutní hodnota reálné části

% Požadované tlumení
zeta = 0.7;

% Výpočet přirozené frekvence (omega_n) z reálné části a tlumení
% Platí: re = zeta * omega_n  =>  omega_n = re / zeta
omega_n = re / zeta;

% Zesílení K_p odpovídá absolutnímu členu v rovnici 2. řádu (omega_n^2)
Kp = omega_n^2; 

% Dopočet integrační konstanty: K(s) = Kp * (s + z)/s = Kp + (Kp*z)/s
Ki = Kp * z;

% Výpis výsledků do konzole
fprintf('Navržené parametry regulátoru:\n');
fprintf('Kp = %.2f\n', Kp);
fprintf('Ki = %.2f\n', Ki);

% 3. Vytvoření regulátoru
C = pid(Kp, Ki);

% 4. Spuštění nástroje pro ověření a splnění bodu c) a d)
% Otevře se interaktivní okno, kde uvidíš Root Locus i s tvým regulátorem
controlSystemDesigner(G, C);