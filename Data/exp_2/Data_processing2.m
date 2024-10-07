% Load the datasets
load T2FPtime.mat;  % First dataset containing Fz
load T2.mat; % Second dataset containing s1, s2, s3, s4, s


%%
% Extract the necessary fields
Fz = T2FPtime.Fz;

%%
disp(T2FPtime(1:5, :));


%%
disp(T2(1:5, :));
%%
currTime_Fz = T2FPtime.currTime; % Timestamps from the first dataset
disp(currTime_Fz);
%%
% Assuming the second dataset is structured similarly to the first one
currTime_Second = T2.currTime; % Timestamps from the second dataset
%%
% Identify timestamps where Fz is zero
zeroFzIndices = find(Fz == 0);
zeroFzTimes = currTime_Fz(zeroFzIndices); % Corresponding timestamps
%%
% Loop through the timestamps with zero Fz and set corresponding values to zero in the second dataset
for i = 1:length(zeroFzTimes)
    % Get the current zero Fz timestamp
    currTimeMatch = zeroFzTimes(i);
    
    % Calculate the absolute differences with all timestamps in the second dataset
    [~, matchIndex] = min(abs(currTime_Second - currTimeMatch));
    
    % Set s1, s2, s3, s4, and s to zero for the nearest timestamp found
    T2.s1(matchIndex) = 0;
    T2.s2(matchIndex) = 0;
    T2.s3(matchIndex) = 0;
    T2.s4(matchIndex) = 0;
    T2.s(matchIndex) = 0;
end
%%
% Optionally, save the updated second dataset if needed
% save('Updated_WithExo_GRF.mat', 'WithExo_GRF');

% Display the updated second dataset for verification (first 5 rows)
disp(T2(1:5, :));
