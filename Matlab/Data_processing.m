clc;
close all;
clear;

% load WithExo_GRF.mat
load T2Copy.mat
load updatedT2FP.mat

%%
fs = 200; 
dt = 1 / fs; 

Fz = T2FPtime.Fz; 
timeFP = (0:length(Fz)-1)' * dt * 1000; % Time in milliseconds

% Add a new field 'currTime' to the existing structure
T2FPtime.currTime = timeFP; 

% Optionally, display the updated structure fields
disp(T2FPtime(1:5, :));

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

% Create a figure with two subplots

% Create a figure with two subplots
figure;

% First subplot for Fz vs timeFP
subplot(2,1,1); % (2 rows, 1 column, 1st plot)
plot(timeFP, abs(Fz), 'b', 'LineWidth', 1.5); % Plot Fz in blue
title('Plot of Fz vs Time');
xlabel('Time (ms)');
ylabel('Fz');
grid on;

% Second subplot for s1, s2, s3, s4, and s vs currTime
subplot(2,1,2); % (2 rows, 1 column, 2nd plot)
hold on; % Hold on to plot multiple lines on the same axis

% Plot each variable in a different color
plot(t, T2.s1, 'r', 'LineWidth', 1.5); % s1 in red
plot(t, T2.s2, 'g', 'LineWidth', 1.5); % s2 in green
plot(t, T2.s3, 'm', 'LineWidth', 1.5); % s3 in magenta
plot(t, T2.s4, 'k', 'LineWidth', 1.5); % s4 in cyan
% plot(t, T2Copy.s, 'k', 'LineWidth', 1.5);  % s in black

% Add legends and titles
title('Plot of s1, s2, s3, s4, and s vs Time');
xlabel('Time');
ylabel('s');
legend('s1', 's2', 's3', 's4', 's', 'Location', 'best');
grid on;

hold off; % Release the hold on the current axis

