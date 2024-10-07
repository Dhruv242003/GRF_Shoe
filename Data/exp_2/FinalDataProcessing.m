
disp(T2(1:5, :));


%%   Single dataset visualization

% Create a figure with a single plot for Fz vs timeFP
figure;

% Plot Fz vs timeFP
plot(timeFP, abs(Fz), 'b', 'LineWidth', 1.5); % Plot Fz in blue
title('Plot of Fz vs Time');
xlabel('Time (ms)');
ylabel('Fz');
grid on;

%% Two data set together


timeFP = T2FPtime.currTime;
t = ShoeProcessed.currTime;

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

hold off; 



%% Removing extra values from shoe dataset and equating to zero

% Extract timestamps from the first dataset
currTime_Fz = T2FPtime.currTime; % Timestamps from the first dataset
disp(currTime_Fz);

% Extract timestamps from the second dataset
currTime_Second = T2.currTime; % Timestamps from the second dataset

% Identify timestamps where Fz is zero
zeroFzIndices = find(Fz == 0);
zeroFzTimes = currTime_Fz(zeroFzIndices); % Corresponding timestamps

% Create a copy of the original second dataset
T2_modified = T2; % Create a new variable for the modified dataset

% Loop through the timestamps with zero Fz and set corresponding values to zero in the modified dataset
for i = 1:length(zeroFzTimes)
    % Get the current zero Fz timestamp
    currTimeMatch = zeroFzTimes(i);
    
    % Calculate the absolute differences with all timestamps in the second dataset
    [~, matchIndex] = min(abs(currTime_Second - currTimeMatch));
    
    % Set s1, s2, s3, s4, and s to zero for the nearest timestamp found in the modified dataset
    T2_modified.s1(matchIndex) = 0;
    T2_modified.s2(matchIndex) = 0;
    T2_modified.s3(matchIndex) = 0;
    T2_modified.s4(matchIndex) = 0;
    T2_modified.s(matchIndex) = 0;
end

% Optionally, save the updated modified dataset to a new file
% save('Updated_WithExo_GRF.mat', 'T2_modified');

% Display the updated modified dataset for verification (first 5 rows)
disp(T2_modified(1:5, :));

%% Mat file to CSV file

writetable(combinedResult, 'combinedResult.csv');

%% Visualization after processing


timeFP = T2FPtime.currTime;
t = ShoeProcessed.currTime;

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

hold off; 


%% InterPolation

ShoeTime = ShoeProcessed.currTime; % Timestamps from the smaller dataset

FPTime = T2FPtime.currTime;        % Timestamps from the larger dataset

% Extract the data columns (excluding currTime) from T2FPtime
if istable(T2FPtime)

    T2FPtimeArray = table2array(T2FPtime(:, 1:end-1)); % Exclude currTime
else
    T2FPtimeArray = T2FPtime(:, 1:end-1); % If already an array, just use indexing
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
if istable(ShoeProcessed)
    combinedResult = [ShoeProcessed, array2table(combinedData, 'VariableNames', T2FPtime.Properties.VariableNames(1:end-1))];
else
    % Adjust if ShoeProcessed is not a table
    combinedResult = [ShoeProcessed, combinedData];
end

% Display the first few rows of the combined data for verification
disp(combinedResult(1:5, :));



%%

writetable(combinedResult, 'combinedResult.csv');
%%

%%

%%