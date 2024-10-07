clc;
close all;
clear;

% load WithExo_GRF.mat
load T2_FP_Copy.mat
%%
fs = 200; 
dt = 1 / fs; 

Fz = updatedT2FP1.Fz; 
timeFP = (0:length(Fz)-1)' * dt * 1000; % Time in milliseconds

% Add a new field 'currTime' to the existing structure
updatedT2FP1.currTime = timeFP; 

% Optionally, display the updated structure fields
disp(updatedT2FP1(1:5, :));

%%
disp(T2(1:5, :));

%%

t = T2.currTime;
s = T2.s;
%%
% Create a figure with two subplots
figure;

% First subplot for Fz vs time_BL
subplot(2,1,1); % (2 rows, 1 column, 1st plot)
plot(timeFP, abs(Fz));
title('Plot of Fz vs Time');
xlabel('Time (ms)');
ylabel('Fz');

% Second subplot for s vs t
subplot(2,1,2); % (2 rows, 1 column, 2nd plot)
plot(t, s);
title('Plot of s vs Time');
xlabel('Time');
ylabel('s');
%%


timeFP = combinedResult.currTime;
t = timeFP;
% Create a figure with two subplots
figure;

% First subplot for Fz vs timeFP
subplot(2,1,1); % (2 rows, 1 column, 1st plot)
plot(timeFP, abs(combinedResult.Fz), 'b', 'LineWidth', 1.5); % Plot Fz in blue
title('Plot of Fz vs Time');
xlabel('Time (ms)');
ylabel('Fz');
grid on;

% Second subplot for s1, s2, s3, s4, and s vs currTime
subplot(2,1,2); % (2 rows, 1 column, 2nd plot)
hold on; % Hold on to plot multiple lines on the same axis

% Plot each variable in a different color
plot(t, combinedResult.s1, 'r', 'LineWidth', 1.5); % s1 in red
plot(t, combinedResult.s2, 'g', 'LineWidth', 1.5); % s2 in green
plot(t, combinedResult.s3, 'm', 'LineWidth', 1.5); % s3 in magenta
plot(t, combinedResult.s4, 'k', 'LineWidth', 1.5); % s4 in cyan
% plot(t, T2Copy.s, 'k', 'LineWidth', 1.5);  % s in black

% Add legends and titles
title('Plot of s1, s2, s3, s4, and s vs Time');
xlabel('Time');
ylabel('s');
legend('s1', 's2', 's3', 's4', 's', 'Location', 'best');
grid on;

hold off; % Release the hold on the current axis


%%
t1 = T2.currTime;
t2 = ShoeProcessed.currTime;

x_min = 10000;
x_max = 80000;

y_min = 14;
y_max = 17;

% Create a figure with two subplots
figure;

% First subplot for T2 data (s1, s2, s3, s4 vs currTime)
subplot(2,1,1); % (2 rows, 1 column, 1st plot)
hold on; % Hold on to plot multiple lines on the same axis

% Plot each variable in a different color
plot(t1, T2.s1, 'r', 'LineWidth', 1.5); % s1 in red
plot(t1, T2.s2, 'g', 'LineWidth', 1.5); % s2 in green
plot(t1, T2.s3, 'm', 'LineWidth', 1.5); % s3 in magenta
plot(t1, T2.s4, 'k', 'LineWidth', 1.5); % s4 in cyan

% Add legends and titles for the first subplot
title('Plot of T2: s1, s2, s3, s4 vs Time');
xlabel('Time');
ylabel('s');
legend('s1', 's2', 's3', 's4', 'Location', 'best');
grid on;
ylim([y_min y_max]);
xlim([x_min x_max]);

hold off; % Release the hold for the first plot

% Second subplot for ShoeProcessed data (s1, s2, s3, s4 vs currTime)
subplot(2,1,2); % (2 rows, 1 column, 2nd plot)
hold on; % Hold on to plot multiple lines on the same axis

% Plot each variable in a different color
plot(t2, ShoeProcessed.s1, 'r', 'LineWidth', 1.5); % s1 in red
plot(t2, ShoeProcessed.s2, 'g', 'LineWidth', 1.5); % s2 in green
plot(t2, ShoeProcessed.s3, 'm', 'LineWidth', 1.5); % s3 in magenta
plot(t2, ShoeProcessed.s4, 'k', 'LineWidth', 1.5); % s4 in cyan

% Add legends and titles for the second subplot
title('Plot of ShoeProcessed: s1, s2, s3, s4 vs Time');
xlabel('Time');
ylabel('s');
legend('s1', 's2', 's3', 's4', 'Location', 'best');
grid on;
ylim([y_min y_max]);
xlim([x_min x_max]);

hold off; % Release the hold for the second plot

