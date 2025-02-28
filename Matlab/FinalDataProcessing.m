load("FPmax.csv");
load("ShowMax.csv");

%%
FP = arpeet;
Shoe = DATA09;
basePath = 'Data\TorrTrials\arp';
weight = 70;

%%
disp(Shoe(1:5, :));

%% Add time coloumn in Force Plate data
fs = 200; 
dt = 1 / fs; 

Fz =  FP.Fz;
timeFP = (0:length(Fz)-1)' * dt * 1000; % Time in milliseconds

% Add a new field 'currTime' to the existing structure
FP.currTime = timeFP; 

% Optionally, display the updated structure fields
disp(FP(1:5, :));

%%   Single dataset visualization

% Create a figure with a single plot for Fz vs timeFP
figure;

% Plot Fz vs timeFP
plot(timeFP, abs(Fz), 'b', 'LineWidth', 1.5); % Plot Fz in blue
title('Plot of Fz vs Time');
xlabel('Time (ms)');
xlim([23000 ,29500]);
ylim([200 ,500]);
ylabel('Fz (N)');
grid on;



%%

% Define the x-axis limits
x_start = 26500;
x_end = 29500;

% Create a figure
figure;

% Plot Fz vs timeFP
plot(timeFP, abs(Fz), 'b', 'LineWidth', 1.5); % Plot Fz in blue
title('Plot of Fz vs Time');
xlabel('Time (ms)');
ylabel('Fz (N)');
grid on;

% Set x-axis limits
xlim([x_start, x_end]);

% Adjust x-axis ticks to start from zero
xticks(linspace(x_start, x_end, 6)); % Adjust the number of ticks as needed
xticklabels(linspace(0, x_end - x_start, 6)); % Relabel ticks starting from zero


%% Two data set together

timeFP = FP.currTime;
t = Shoe.currTime;

figure;

% First subplot for Fz vs timeFP
subplot(2,1,1); % (2 rows, 1 column, 1st plot)
plot(timeFP, abs(FP.Fz), 'b', 'LineWidth', 1.5); % Plot Fz in blue
title('Plot of Fz vs Time');
xlabel('Time (ms)');
ylabel('Fz');
grid on;

% Set x-axis limits for the first plot
% xlim([0 max(timeFP)]);

% Second subplot for s1, s2, s3, s4, and s vs currTime
subplot(2,1,2); % (2 rows, 1 column, 2nd plot)
hold on; % Hold on to plot multiple lines on the same axis

% Plot each variable in a different color
plot(t, Shoe.s1, 'r', 'LineWidth', 1.5); % s1 in red
plot(t, Shoe.s2, 'g', 'LineWidth', 1.5); % s2 in green
plot(t, Shoe.s3, 'm', 'LineWidth', 1.5); % s3 in magenta
plot(t, Shoe.s4, 'k', 'LineWidth', 1.5); % s4 in cyan
% plot(t, T2Copy.s, 'k', 'LineWidth', 1.5);  % s in black

% Add legends and titles
title('Plot of s1, s2, s3, s4, and s vs Time');
xlabel('Time');
ylabel('s');
legend('Heel', 'Meta 45', 'Toe ', 'Meta 12', 'Avg', 'Location', 'best');
grid on;

% Set x-axis limits for the second plot to match the first plot
% xlim([0 max(t)]);

hold off;

%%
% Second plot for s1, s2, s3, s4, and s vs currTime
figure; % Create a new figure

hold on; % Hold on to plot multiple lines on the same axis

% Plot each variable in a different color
plot(t, Shoe.s1, 'k', 'LineWidth', 1.5); % s1 in red
plot(t, Shoe.s2, 'g', 'LineWidth', 1.5); % s2 in green
plot(t, Shoe.s3, 'm', 'LineWidth', 1.5); % s3 in magenta
plot(t, Shoe.s4, 'k', 'LineWidth', 1.5); % s4 in cyan
% plot(t, T2Copy.s, 'k', 'LineWidth', 1.5);  % s in black

% Add legends and titles
title('Plot of s1, s2, s3, s4, and s vs Time');
xlabel('Time');
ylabel('s');
ylim([700 900]);
xlim([20000,70000]);
legend('s1', 's2', 's3', 's4', 's', 'Location', 'best');
grid on;

% Set x-axis limits if needed (optional)
% xlim([0 max(t)]);

hold off;

%% Removing extra values from shoe dataset and equating to zero

% Extract timestamps from the first dataset
currTime_Fz = FP.currTime; % Timestamps from the first dataset
disp(currTime_Fz);

% Extract timestamps from the second dataset
currTime_Second = Shoe.currTime; % Timestamps from the second dataset

% Identify timestamps where Fz is zero
zeroFzIndices = find(Fz == 0);
zeroFzTimes = currTime_Fz(zeroFzIndices); % Corresponding timestamps

% Create a copy of the original second dataset
Shoe_modified = Shoe; % Create a new variable for the modified dataset

% Loop through the timestamps with zero Fz and set corresponding values to zero in the modified dataset
for i = 1:length(zeroFzTimes)
    % Get the current zero Fz timestamp
    currTimeMatch = zeroFzTimes(i);
    
    % Calculate the absolute differences with all timestamps in the second dataset
    [~, matchIndex] = min(abs(currTime_Second - currTimeMatch));
    
    % Set s1, s2, s3, s4, and s to zero for the nearest timestamp found in the modified dataset
    Shoe_modified.s1(matchIndex) = 0;
    Shoe_modified.s2(matchIndex) = 0;
    Shoe_modified.s3(matchIndex) = 0;
    Shoe_modified.s4(matchIndex) = 0;
    Shoe_modified.s(matchIndex) = 0;
end

% Optionally, save the updated modified dataset to a new file
% save('Updated_WithExo_GRF.mat', 'T2_modified');

% Display the updated modified dataset for verification (first 5 rows)
disp(Shoe_modified(1:5, :));

%% Mat file to CSV file

writetable(Shoe_modified, fullfile(basePath,'Shoe_modified.csv'));

%% Visualization after processing


timeFP = FP.currTime;
t = Shoe_modified.currTime;

figure;

% First subplot for Fz vs timeFP
subplot(2,1,1); % (2 rows, 1 column, 1st plot)
plot(timeFP, abs(FP.Fz), 'b', 'LineWidth', 1.5); % Plot Fz in blue
title('Plot of Fz vs Time');
xlabel('Time (ms)');
ylabel('Fz');
grid on;

% Second subplot for s1, s2, s3, s4, and s vs currTime
subplot(2,1,2); % (2 rows, 1 column, 2nd plot)
hold on; % Hold on to plot multiple lines on the same axis

% Plot each variable in a different color
plot(t, Shoe_modified.s1, 'r', 'LineWidth', 1.5); % s1 in red
plot(t, Shoe_modified.s2, 'g', 'LineWidth', 1.5); % s2 in green
plot(t, Shoe_modified.s3, 'm', 'LineWidth', 1.5); % s3 in magenta
plot(t, Shoe_modified.s4, 'k', 'LineWidth', 1.5); % s4 in cyan
% plot(t, T2Copy.s, 'k', 'LineWidth', 1.5);  % s in black
ylim([700, 850]);
xlim([0, max(t)]);
% Add legends and titles
title('Plot of s1, s2, s3, s4, and s vs Time');
xlabel('Time');
ylabel('s');
legend('s1', 's2', 's3', 's4', 's', 'Location', 'best');
grid on;

hold off; 


%% InterPolation

ShoeTime = Shoe_modified.currTime; % Timestamps from the smaller dataset

FPTime = FP.currTime;        % Timestamps from the larger dataset

% Extract the data columns (excluding currTime) from T2FPtime
if istable(FP)

    T2FPtimeArray = table2array(FP(:, 1:end-1)); % Exclude currTime
else
    T2FPtimeArray = FP(:, 1:end-1); % If already an array, just use indexing
end

% Initialize a matrix to store the combined data
combinedData = nan(length(ShoeTime), size(T2FPtimeArray, 2));

% Loop through each timestamp in the smaller dataset and find the nearest timestamp in the larger dataset
for i = 1:length(ShoeTime)
    % Find the index of the nearest timestamp in the larger dataset
    [~, idx] = min(abs(FPTime - ShoeTime(i)));
    
    % Store the corresponding data from the large dataset in the combined dataset
    combinedData(i, :) = T2FPtimeArray(idx, :);
end

% Convert combinedData to a table and append it to ShoeProcessed
if istable(Shoe_modified)
    combinedResult = [Shoe_modified, array2table(combinedData, 'VariableNames', FP.Properties.VariableNames(1:end-1))];
else
    % Adjust if ShoeProcessed is not a table
    combinedResult = [Shoe_modified, combinedData];
end

% Display the first few rows of the combined data for verification
disp(combinedResult(1:5, :));

%% Adding weight of subject

weight = repmat(weight, height(combinedResult), 1);
combinedResult.Weight = weight;


%%

% Filter rows where s is not equal to 0
combinedResult = combinedResult(combinedResult.s ~= 0, :);
writetable(combinedResult, fullfile(basePath,'combinedResult.csv'));
%%

%%

%%