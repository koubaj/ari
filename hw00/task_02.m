figure;
t = [0:0.05:2];
x1=(2*exp(-3*t) .* cos(2*t) - 3*exp(-3*t) .* sin(2*t));
x2=-1/2*exp(-3*t) .* sin(2*t);

% ... (previous code)
plot(t, x1, 'b');
hold on;
plot(t, x2, 'r');
yline(0, 'k-', 'LineWidth', 1);
hold off;

title('Časové průběhy řešení soustavy dif. rovnic');
xlabel('time [s]');
ylabel('x(t) [-]');
legend('x_1(t)', 'x_2(t)');