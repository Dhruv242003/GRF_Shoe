% Load the data (assuming it is in a CSV file)
data = RIGHTDATA00; % Replace 'your_file.csv' with the actual filename

% Extract relevant columns
currTime = data.currTime;
GRF = data.GRF;

% Plot GRF vs. currTime
figure;
plot(currTime, GRF, 'b-', 'LineWidth', 1.5);
xlabel('Time (s)');
ylabel('Ground Reaction Force (GRF)');
title('GRF vs. Time');
grid on;
