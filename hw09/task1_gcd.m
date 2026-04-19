clear; clc;

syms s;

a = s^2+ 5*s +4;
b = s + 1;
c = s^3 + 13*s^2 + 49*s +37;

gcd_ab = gcd(a, b)
[quotient, remainder] = quorem(c, gcd_ab, s)
