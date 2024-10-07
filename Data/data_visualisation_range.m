t = Walking.currTime;


t_min = 12000;  % Set the start time
t_max = 30000; % Set the end time

% Logical indexing to select the data within the time range
selected_indices = (t >= t_min) & (t <= t_max);

t_selected = t(selected_indices);
s1 = Walking.s1(selected_indices);
s2 = Walking.s2(selected_indices);
s3 = Walking.s3(selected_indices);
s4 = Walking.s4(selected_indices);

% t_selected = t;
% s1 = Walking.s1;
% s2 = Walking.s2;
% s3 = Walking.s3;
% s4 = Walking.s4;

% Start plotting
figure; % Create a new figure window
hold on; % Hold the plot to allow multiple lines on the same plot

% Plot each variable in a different color
plot(t_selected, s1, 'r', 'LineWidth', 1.5); % s1 in red
plot(t_selected, s2, 'g', 'LineWidth', 1.5); % s2 in green
plot(t_selected, s3, 'm', 'LineWidth', 1.5); % s3 in magenta
plot(t_selected, s4, 'k', 'LineWidth', 1.5); % s4 in cyan

% Add legends and titles
title('Plot of s1, s2, s3, s4 vs Time');
xlabel('Time');
ylabel('s');
legend('s1', 's2', 's3', 's4', 'Location', 'best');

grid on; % Turn on the grid
hold off; % Release the hold on the current axis


%%