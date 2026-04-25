%clear; clc;

%% 1. Define S-Function Constants
g = 9.80665;       % [m/s^2]
M = 0.5;           % [kg] cart mass
m = 0.275;         % [kg] pendulum mass
l = 0.1;           % [m] pendulum length
b = 0.21;          % [] friction constant of the cart
dlt = 0.0028;      % [] friction constant of the pivot
kf = 0.1;          % [N/V] input voltage to force ratio
J = m*l^2/3;       % [kg/m^2] pendulum moment of inertia

% Lumped constants
k1 = m*(l/2)/(M+m);
kb = b/(M+m);
ku = kf/(M+m);
k2 = m*g*(l/2)/J;
k3 = m*(l/2)/J;
kd = 2*dlt/J;

%% 2. Define Symbolic Variables and Equations
syms v y w phi u real

% State vector matching your S-Function order
X = [v; y; w; phi]; 

% Non-linear equations of motion (Derivatives)
dv = (k1*sin(phi)*(kd*w + k2*cos(phi)))/(k1*k3*sin(phi)^2 - 1) - (k1*cos(phi)*w^2 + ku*u - kb*v)/(k1*k3*sin(phi)^2 - 1);
dy = v;
dw = (kd*w + k2*cos(phi))/(k1*k3*sin(phi)^2 - 1) - (k3*sin(phi)*(k1*cos(phi)*w^2 + ku*u - kb*v))/(k1*k3*sin(phi)^2 - 1);
dphi = w;

% Full state derivative vector
f = [dv; dy; dw; dphi];

%% 3. Compute Symbolic Jacobians
A_sym = jacobian(f, X);
B_sym = jacobian(f, u);

%% 4. Evaluate at UP Position (Unstable: phi = pi/2)
% Equilibrium states: [v=0; y=0; w=0; phi=pi/2], u=0
X_up = [0; 0; 0; pi/2];
u_eq = 0;

A_up = double(subs(A_sym, [X; u], [X_up; u_eq]));
B_up = double(subs(B_sym, [X; u], [X_up; u_eq]));

disp('==================================================')
disp('   UP POSITION (phi = pi/2 / 90 deg) - UNSTABLE   ')
disp('==================================================')
disp('A_up Matrix:'); disp(A_up)
disp('B_up Matrix:'); disp(B_up)

% Check eigenvalues to confirm instability
disp('Eigenvalues of A_up (Positive real part = Unstable):')
disp(eig(A_up))

%% 5. Evaluate at DOWN Position (Stable: phi = -pi/2)
% Equilibrium states: [v=0; y=0; w=0; phi=-pi/2], u=0
X_down = [0; 0; 0; -pi/2];

A_down = double(subs(A_sym, [X; u], [X_down; u_eq]));
B_down = double(subs(B_sym, [X; u], [X_down; u_eq]));

disp('==================================================')
disp('  DOWN POSITION (phi = -pi/2 / -90 deg) - STABLE  ')
disp('==================================================')
disp('A_down Matrix:'); disp(A_down)
disp('B_down Matrix:'); disp(B_down)

% Check eigenvalues to confirm stability
disp('Eigenvalues of A_down (All negative real parts = Stable):')
disp(eig(A_down))

%% 6. Creating a transfer function
C_phi = [0, 0, 0, 1];
D_phi = 0;
C = [0 1 0 0;
     0 0 0 1];
D = [0; 0];

% State space
sys_ss_up =  ss(A_up, B_up, C, D);
sys_ss_down =  ss(A_down, B_down, C, D);

% Transfer
sys_tf_up = (sys_ss_up);
sys_tf_down = tf(sys_ss_down);

disp('Přenosová funkce G(s) pro úhel kyvadla v horní úvrati:');
sys_tf_up
sys_tf_down

%% rtool
G1 = sys_ss_down(1, 1);

%rltool(G1);

Kp = 7.94;
Ki = 0.882;
Kd = 12.6;