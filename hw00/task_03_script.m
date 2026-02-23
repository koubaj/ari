figure;
plot(out.nonlinear.Time, out.nonlinear.Data, 'b');
hold on;
plot(out.linear.Time, out.linear.Data, 'r');
hold off;

grid on;
title("Porovnání lineárního a nelineárního systému");
xlabel('Čas [s]');
ylabel('Výstup y [-]');
legend('Nelineární model', 'Linearizovaný model', 'Location', 'best');
