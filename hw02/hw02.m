A = [0 0 0 1 0 0;
     0 0 0 0 1 0;
     0 0 0 0 0 1;
     7.3809 0 0 0 2 0;
     0 -2.1904 0 -2 0 0;
     0 0 -3.1904 0 0 0];

B1 = [0; 0; 0; 1; 0; 0];
B2 = [0; 0; 0; 0; 1; 0];
B3 = [0; 0; 0; 0; 0; 1];

%% task 01
eigen_vals = eig(A);

%% task 02
E1 = ctrb(A, B1);
E2 = ctrb(A, B2);
E3 = ctrb(A, B3);

% n = 6
R1 = rank(E1);
R2 = rank(E2);
R3 = rank(E3);

%% task 03
syms s;
I = eye(size(A));
H1 = inv(s*I - A) * B1;
H2 = inv(s*I - A) * B2;
H3 = inv(s*I - A) * B3;

%% task 04
B = [B1, B2, B3];
E = ctrb(A, B);
R = rank(E);

%% task 05
H = inv(s*I - A) * B;