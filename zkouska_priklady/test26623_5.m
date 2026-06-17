s = tf('s');
T = 1/(s+2);
G = (s);

Transfer = T*G

sys = tf(1, [1, 2]);

step(Transfer)
grid on

