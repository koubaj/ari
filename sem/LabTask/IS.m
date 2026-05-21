zeta_cl = 0.103703; 
wn_cl = 10.91061;

% Klasický IS
K_shaper = exp((-zeta_cl * pi) / sqrt(1 - zeta_cl^2));
t2 = pi / (wn_cl * sqrt(1 - zeta_cl^2)); 
A1 = 1 / (1 + K_shaper); 
A2 = K_shaper / (1 + K_shaper); 

% DZV Shaper
beta = zeta_cl * wn_cl;
Omega = wn_cl * sqrt(1 - zeta_cl^2);
f_opt = @(th) Omega*exp(-beta*th) + beta*sin(Omega*th) - Omega*cos(Omega*th);
theta_dzv = fzero(f_opt, [pi/Omega, 2*pi/Omega]);
B_dzv = sin(Omega*theta_dzv) / (sin(Omega*theta_dzv) - theta_dzv*Omega*exp(-beta*theta_dzv));
K_int = (1 - B_dzv) / theta_dzv;