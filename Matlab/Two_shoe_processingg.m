%%
% Froce Plate Data extraction

FP_data = sitting;
basePath = 'Data\TwoShoes\Krunal\sitting';
weight = 82;


%%
Fz_Right = FP_data.Fz1;
Fz_Left = FP_data.Fz2;

%%
plot(Fz_Right);

%% Add time coloumn in Force Plate data

fs = 200; 
dt = 1 / fs; 
timeFP = (0:length(Fz_Right)-1)' * dt * 1000; % Time in milliseconds
FP_data.currTime = timeFP; 
disp(FP_data(1:5, :));


%%

figure;
plot(timeFP, abs(Fz_Right), 'b', 'LineWidth', 1.5); 
hold on;
plot(timeFP, abs(Fz_Left), 'r', 'LineWidth', 1.5);
title('Plot of Fz vs Time');
xlabel('Time (ms)');
ylabel('Force (N)');
legend('Fz\_Right', 'Fz\_Left');
grid on;
hold off;



%%  
figure;

subplot(2,1,1);
plot(timeFP, abs(Fz_Right), 'b', 'LineWidth', 1.5); 
title('Plot of Fz\_Right vs Time');
xlabel('Time (ms)');
ylabel('Fz\_Right (N)');
grid on;

subplot(2,1,2);
plot(timeFP, abs(Fz_Left), 'r', 'LineWidth', 1.5); 
title('Plot of Fz\_Left vs Time');
xlabel('Time (ms)');
ylabel('Fz\_Left (N)');
grid on;



%% SHOE DATA IMPORTING
Left_shoe = LEFTDATA00;
Right_shoe = RIGHTDATA00;

%% Truncating the size of bigger shoe data

% Find the minimum timestamp
min_time = min(Left_shoe.currTime(end), Right_shoe.currTime(end));

% Truncate based on timestamps, not index
Left_shoe = Left_shoe(Left_shoe.currTime <= min_time, :);
Right_shoe = Right_shoe(Right_shoe.currTime <= min_time, :);


%%
plot(Left_shoe.s);
hold on;
plot(Right_shoe.s);
hold off;

%% Left force Plate and Left Shoe

timeFP = FP_data.currTime;
t = Left_shoe.currTime;

figure;
subplot(2,1,1);
plot(timeFP, abs(Fz_Left), 'b', 'LineWidth', 1.5);
title('Plot of Fz Left ForcePlate vs Time');
xlabel('Time (ms)');
ylabel('Fz_Left');
grid on;

subplot(2,1,2);
hold on;

plot(t, Left_shoe.s1, 'r', 'LineWidth', 1.5);
plot(t, Left_shoe.s2, 'g', 'LineWidth', 1.5);
plot(t, Left_shoe.s3, 'm', 'LineWidth', 1.5); 
plot(t, Left_shoe.s4, 'k', 'LineWidth', 1.5); 

title('Plot of Left Shoe s1, s2, s3, s4, and s vs Time');
xlabel('Time (ms)');
ylabel('Pressure (Torr)');
legend('Heel', 'Meta 45', 'Toe ', 'Meta 12', 'Avg', 'Location', 'best');
grid on;

hold off;

%% Right force Plate and Right Shoe

timeFP = FP_data.currTime;
t = Right_shoe.currTime;

figure;
subplot(2,1,1);
plot(timeFP, abs(Fz_Right), 'b', 'LineWidth', 1.5);
title('Plot of Fz Right ForcePlate vs Time');
xlabel('Time (ms)');
ylabel('Right_shoe');
grid on;

subplot(2,1,2);
hold on;

plot(t, Right_shoe.s1, 'r', 'LineWidth', 1.5);
plot(t, Right_shoe.s2, 'g', 'LineWidth', 1.5);
plot(t, Right_shoe.s3, 'm', 'LineWidth', 1.5); 
plot(t, Right_shoe.s4, 'k', 'LineWidth', 1.5); 

title('Plot of Right Shoe s1, s2, s3, s4, and s vs Time');
xlabel('Time (ms)');
ylabel('Pressure (Torr)');
legend('Heel', 'Meta 45', 'Toe ', 'Meta 12', 'Avg', 'Location', 'best');
grid on;

hold off;

%% ALL DATA TOGETHER

figure;

% Left Foot Force Plate
subplot(2,2,1);
plot(FP_data.currTime, abs(Fz_Left), 'b', 'LineWidth', 1.5);
title('Fz Left Force Plate vs Time');
xlabel('Time (ms)');
ylabel('Force (N)');
grid on;

% Left Shoe Pressure Sensors
subplot(2,2,3);
hold on;
plot(Left_shoe.currTime, Left_shoe.s1, 'r', 'LineWidth', 1.5);
plot(Left_shoe.currTime, Left_shoe.s2, 'g', 'LineWidth', 1.5);
plot(Left_shoe.currTime, Left_shoe.s3, 'm', 'LineWidth', 1.5); 
plot(Left_shoe.currTime, Left_shoe.s4, 'k', 'LineWidth', 1.5); 
title('Left Shoe Pressure vs Time');
xlabel('Time (ms)');
ylabel('Pressure (Torr)');
legend('Heel', 'Meta 45', 'Toe', 'Meta 12', 'Location', 'best');
grid on;
hold off;

% Right Foot Force Plate
subplot(2,2,2);
plot(FP_data.currTime, abs(Fz_Right), 'b', 'LineWidth', 1.5);
title('Fz Right Force Plate vs Time');
xlabel('Time (ms)');
ylabel('Force (N)');
grid on;

% Right Shoe Pressure Sensors
subplot(2,2,4);
hold on;
plot(Right_shoe.currTime, Right_shoe.s1, 'r', 'LineWidth', 1.5);
plot(Right_shoe.currTime, Right_shoe.s2, 'g', 'LineWidth', 1.5);
plot(Right_shoe.currTime, Right_shoe.s3, 'm', 'LineWidth', 1.5); 
plot(Right_shoe.currTime, Right_shoe.s4, 'k', 'LineWidth', 1.5); 
title('Right Shoe Pressure vs Time');
xlabel('Time (ms)');
ylabel('Pressure (Torr)');
legend('Heel', 'Meta 45', 'Toe', 'Meta 12', 'Location', 'best');
grid on;
hold off;

sgtitle('Force Plate and Shoe Pressure Comparison');

%% Removing extra values from shoe dataset and equating to zero

currTime_Fz = FP_data.currTime;


currTime_LeftShoe = Left_shoe.currTime;
currTime_RightShoe = Right_shoe.currTime;

% Identify timestamps where Fz is zero
zeroFzLeftIndices = find(Fz_Left == 0);
zeroFzLeftTimes = currTime_Fz(zeroFzLeftIndices);

zeroFzRightIndices = find(Fz_Right == 0);
zeroFzRightTimes = currTime_Fz(zeroFzRightIndices);


Left_shoe_modified = Left_shoe;
Right_shoe_modified = Right_shoe;


for i = 1:length(zeroFzLeftTimes)

    currTimeMatch = zeroFzLeftTimes(i);
    
    % Calculate the absolute differences with all timestamps in the second dataset
    [~, matchIndex] = min(abs(currTime_LeftShoe - currTimeMatch));
    
    % Set s1, s2, s3, s4, and s to zero for the nearest timestamp found in the modified dataset
    Left_shoe_modified.s1(matchIndex) = 0;
    Left_shoe_modified.s2(matchIndex) = 0;
    Left_shoe_modified.s3(matchIndex) = 0;
    Left_shoe_modified.s4(matchIndex) = 0;
    Left_shoe_modified.s(matchIndex) = 0;
end

for i = 1:length(zeroFzRightTimes)

    currTimeMatch = zeroFzRightTimes(i);
    
    % Calculate the absolute differences with all timestamps in the second dataset
    [~, matchIndex] = min(abs(currTime_RightShoe - currTimeMatch));
    
    % Set s1, s2, s3, s4, and s to zero for the nearest timestamp found in the modified dataset
    Right_shoe_modified.s1(matchIndex) = 0;
    Right_shoe_modified.s2(matchIndex) = 0;
    Right_shoe_modified.s3(matchIndex) = 0;
    Right_shoe_modified.s4(matchIndex) = 0;
    Right_shoe_modified.s(matchIndex) = 0;
end

%% Visualization after processing

figure;

% Left Foot Force Plate
subplot(2,2,1);
plot(FP_data.currTime, abs(Fz_Left), 'b', 'LineWidth', 1.5);
title('Fz Left Force Plate vs Time');
xlabel('Time (ms)');
ylabel('Force (N)');
grid on;

% Left Shoe Pressure Sensors
subplot(2,2,3);
hold on;
plot(Left_shoe_modified.currTime, Left_shoe_modified.s1, 'r', 'LineWidth', 1.5);
plot(Left_shoe_modified.currTime, Left_shoe_modified.s2, 'g', 'LineWidth', 1.5);
plot(Left_shoe_modified.currTime, Left_shoe_modified.s3, 'm', 'LineWidth', 1.5); 
plot(Left_shoe_modified.currTime, Left_shoe_modified.s4, 'k', 'LineWidth', 1.5); 
title('Left Shoe Pressure vs Time');
xlabel('Time (ms)');
ylabel('Pressure (Torr)');
legend('Heel', 'Meta 45', 'Toe', 'Meta 12', 'Location', 'best');
grid on;
hold off;

% Right Foot Force Plate
subplot(2,2,2);
plot(FP_data.currTime, abs(Fz_Right), 'b', 'LineWidth', 1.5);
title('Fz Right Force Plate vs Time');
xlabel('Time (ms)');
ylabel('Force (N)');
grid on;

% Right Shoe Pressure Sensors
subplot(2,2,4);
hold on;
plot(Right_shoe_modified.currTime, Right_shoe_modified.s1, 'r', 'LineWidth', 1.5);
plot(Right_shoe_modified.currTime, Right_shoe_modified.s2, 'g', 'LineWidth', 1.5);
plot(Right_shoe_modified.currTime, Right_shoe_modified.s3, 'm', 'LineWidth', 1.5); 
plot(Right_shoe_modified.currTime, Right_shoe_modified.s4, 'k', 'LineWidth', 1.5); 
title('Right Shoe Pressure vs Time');
xlabel('Time (ms)');
ylabel('Pressure (Torr)');
legend('Heel', 'Meta 45', 'Toe', 'Meta 12', 'Location', 'best');
grid on;
hold off;

sgtitle('Force Plate and Shoe Pressure Comparison');


%% InterPolation
LeftShoeTime = Left_shoe_modified.currTime; % Timestamps from the left shoe dataset
RightShoeTime = Right_shoe_modified.currTime; % Timestamps from the right shoe dataset

FPTime = FP_data.currTime; % Timestamps from the force plate dataset

if istable(FP_data)
    FPDataArray = table2array(FP_data(:, 1:end-1)); % Exclude currTime
else
    FPDataArray = FP_data(:, 1:end-1); % If already an array, just use indexing
end

combinedData_Left = nan(length(LeftShoeTime), size(FPDataArray, 2));
combinedData_Right = nan(length(RightShoeTime), size(FPDataArray, 2));

for i = 1:length(LeftShoeTime)
    [~, idx] = min(abs(FPTime - LeftShoeTime(i))); % Find nearest index
    combinedData_Left(i, :) = FPDataArray(idx, :); % Store corresponding data
end

for i = 1:length(RightShoeTime)
    [~, idx] = min(abs(FPTime - RightShoeTime(i))); % Find nearest index
    combinedData_Right(i, :) = FPDataArray(idx, :); % Store corresponding data
end

if istable(Left_shoe_modified)
    Left_shoe_processed = [Left_shoe_modified, array2table(combinedData_Left, 'VariableNames', FP_data.Properties.VariableNames(1:end-1))];
else
    Left_shoe_processed = [Left_shoe_modified, combinedData_Left];
end

if istable(Right_shoe_modified)
    Right_shoe_processed = [Right_shoe_modified, array2table(combinedData_Right, 'VariableNames', FP_data.Properties.VariableNames(1:end-1))];
else
    Right_shoe_processed = [Right_shoe_modified, combinedData_Right];
end

% Add weight column to Left Shoe Processed
weightLeft = repmat(weight, height(Left_shoe_processed), 1);
Left_shoe_processed.Weight = weightLeft;

% Add weight column to Right Shoe Processed
weightRight = repmat(weight, height(Right_shoe_processed), 1);
Right_shoe_processed.Weight = weightRight;

% Display the first few rows of the processed datasets for verification
disp(Left_shoe_processed(1:5, :));
disp(Right_shoe_processed(1:5, :));


%%

% Filter rows where s is not equal to 0
Left_shoe_processed = Left_shoe_processed(Left_shoe_processed.s ~= 0, :);
Left_shoe_processed.Fx = Left_shoe_processed.Fx2;
Left_shoe_processed.Fy = Left_shoe_processed.Fy2;
Left_shoe_processed.Fz = Left_shoe_processed.Fz2;
Left_shoe_processed.Mx = Left_shoe_processed.Mx2;
Left_shoe_processed.My = Left_shoe_processed.My2;
Left_shoe_processed.Mz = Left_shoe_processed.Mz2;
Left_shoe_processed.Cx = Left_shoe_processed.Cx2;
Left_shoe_processed.Cy = Left_shoe_processed.Cy2;
Left_shoe_processed.Cz = Left_shoe_processed.Cz2;

Left_shoe_processed = removevars(Left_shoe_processed, {'Fx1','Fy1','Fz1', 'Mx1','My1','Mz1', 'Cx1','Cy1','Cz1','Fx2', 'Fy2','Fz2','Mx2','My2','Mz2', 'Cx2','Cy2','Cz2'});


Right_shoe_processed = Right_shoe_processed(Right_shoe_processed.s ~= 0, :);
Right_shoe_processed.Fx = Right_shoe_processed.Fx1;
Right_shoe_processed.Fy = Right_shoe_processed.Fy1;
Right_shoe_processed.Fz = Right_shoe_processed.Fz1;
Right_shoe_processed.Mx = Right_shoe_processed.Mx1;
Right_shoe_processed.My = Right_shoe_processed.My1;
Right_shoe_processed.Mz = Right_shoe_processed.Mz1;
Right_shoe_processed.Cx = Right_shoe_processed.Cx1;
Right_shoe_processed.Cy = Right_shoe_processed.Cy1;
Right_shoe_processed.Cz = Right_shoe_processed.Cz1;

Right_shoe_processed = removevars(Right_shoe_processed, {'Fx1','Fy1','Fz1', 'Mx1','My1','Mz1', 'Cx1','Cy1','Cz1','Fx2', 'Fy2','Fz2','Mx2','My2','Mz2', 'Cx2','Cy2','Cz2'});


writetable(Left_shoe_processed, fullfile(basePath,'Left_shoe_processed.csv'));
writetable(Right_shoe_processed, fullfile(basePath,'Right_shoe_processed.csv'));

