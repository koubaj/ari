clear; clc;

% 1. Definujeme proměnnou 's' jako POLYNOM (tohle nahrazuje syms s)
s = tf('s'); 

% 2. Zapíšeme rovnice přesně tak, jak je vidíme na papíře
a = s^2 + 5*s + 4;
b = s + 1;
c = s^3 + 13*s^2 + 49*s + 37;

% 3. Spustíme výpočet pro minimální Y
[x_syl, y_syl] = axbyc(a, b, c, 'syl')
[x_minx, y_minx] = axbyc(a, b, c, 'minx')
[x_miny, y_miny] = axbyc(a, b, c, 'miny')