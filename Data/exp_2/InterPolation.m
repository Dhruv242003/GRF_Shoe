% Check if 'currTime' columns are already numeric arrays or tables

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
% Extract the Fz values and corresponding time (currTime) from the original T2FPtime
% Extract the Fz values and corresponding time (currTime) from the original T2FPtime
Fz_original = T2FPtime.Fz;
time_original = T2FPtime.currTime;

% Extract the Fz values and corresponding time (currTime) from the combined result
Fz_combined = combinedResult.Fz;
time_combined = combinedResult.currTime;

% Create a figure
figure;

% First subplot for original T2FPtime Fz vs Time
subplot(2, 1, 1); % 2 rows, 1 column, 1st plot
plot(time_original, Fz_original, 'r', 'LineWidth', 1.5); % Red line for original data
title('Fz vs Time - Original T2FPtime');
xlabel('Time (ms)');
ylabel('Fz');
grid on;

% Second subplot for combined result Fz vs Time
subplot(2, 1, 2); % 2 rows, 1 column, 2nd plot
plot(time_combined, Fz_combined, 'b', 'LineWidth', 1.5); % Blue line for combined result
title('Fz vs Time - Combined Result');
xlabel('Time (ms)');
ylabel('Fz');
grid on;

%%

writetable(combinedResult, 'combinedResult.csv');

