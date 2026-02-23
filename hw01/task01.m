figure;
plot(out.nonLinear.Time, out.nonLinear.Data, 'b');

title('Nelineární model');
xlabel('čas [t]');
ylabel('rychlost v[m*s]');
grid on;

figure;
plot(out.linear.Time, out.linear.Data, 'r');

title('Lineární model');
xlabel('čas [t]');
ylabel('rychlost v[m/s]');
grid on;