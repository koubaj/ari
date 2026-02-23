% 1. Definice proměnné 's' pro Laplaceovu transformaci
s = tf('s');

% 2. Zápis přenosové funkce G1(s) přesně podle zadání
G1 = (s - 1) / ((s + 10) * (s - 10) * (s + 80));

% 3. Vykreslení Bodeho charakteristiky
figure;
bode(G1);

% 4. Zapnutí mřížky (velmi doporučeno pro kontrolu asymptot)
grid on;