s = tf('s');
F = (1+s)/(9+s^2);

Kp = 2;
Ki = 5; 
Kd = 10;

C = pid(Kp, Ki, Kd);
T = feedback(C*F, 1);
pole(T)