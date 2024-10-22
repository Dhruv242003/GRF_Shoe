import pandas as pd 
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import torch
import torch.nn as nn
import matplotlib.pyplot as plt

# Define your file paths
excel_file_path = [
    'D:/Projectcourse_vineet/Dataset/Ansh/Final_T1 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Ansh/Final_T2 - Sheet1.csv',
    # 'D:/Projectcourse_vineet/Dataset/Ansh/Final_T3 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Ansh/Final_T4 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Ansh/Final_t5 - Sheet1.csv',
     
    'D:/Projectcourse_vineet/Dataset/Arun/Final_t1 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Arun/Final_T2 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Arun/Final_T3 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Arun/Final_T4 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Arun/Final_T5 - Sheet1.csv',
    # 'D:/Projectcourse_vineet/Dataset/Himanshu/Final_T1 - T1_Squats.csv',
    'D:/Projectcourse_vineet/Dataset/Himanshu/Final_T2 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Himanshu/Final_T3 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Himanshu/Final_T4 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Himanshu/Final_t5 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Smit/Final_T1 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Smit/Final_t2 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Smit/Final_t3 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Smit/Final_T4 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/Smit/Final_T5 - Sheet1.csv',
    'D:/Projectcourse_vineet/Dataset/s1/p1.csv',
    'D:/Projectcourse_vineet/Dataset/s1/p2.csv',
     'D:/Projectcourse_vineet/Dataset/s1/p3.csv',
     'D:/Projectcourse_vineet/Dataset/s1/p4.csv',
     'D:/Projectcourse_vineet/Dataset/s1/p5.csv',
     'D:/Projectcourse_vineet/Dataset/s2/p1.csv',
     'D:/Projectcourse_vineet/Dataset/s2/p3.csv',
     'D:/Projectcourse_vineet/Dataset/s2/p4.csv',
     'D:/Projectcourse_vineet/Dataset/s2/p5.csv',
     'D:/Projectcourse_vineet/Dataset/s3/p1.csv',
     'D:/Projectcourse_vineet/Dataset/s3/p2.csv',
     'D:/Projectcourse_vineet/Dataset/s3/p3.csv',
     'D:/Projectcourse_vineet/Dataset/s3/p4.csv',
    'D:/Projectcourse_vineet/Dataset/s3/p5.csv',
     'D:/Projectcourse_vineet/Dataset/s4/p1.csv',
     'D:/Projectcourse_vineet/Dataset/s4/p2.csv',
     'D:/Projectcourse_vineet/Dataset/s4/p3.csv',
    'D:/Projectcourse_vineet/Dataset/s4/p4.csv',
     'D:/Projectcourse_vineet/Dataset/s4/p5.csv',
     'D:/Projectcourse_vineet/Dataset/s5/p1.csv',
    'D:/Projectcourse_vineet/Dataset/s5/p2.csv',
     'D:/Projectcourse_vineet/Dataset/s5/p3.csv',
     'D:/Projectcourse_vineet/Dataset/s5/p4.csv',
     'D:/Projectcourse_vineet/Dataset/s5/p5.csv',
     'D:/Projectcourse_vineet/Dataset/s6/p1.csv',
    'D:/Projectcourse_vineet/Dataset/s6/p2.csv',
     'D:/Projectcourse_vineet/Dataset/s6/p3.csv',
     'D:/Projectcourse_vineet/Dataset/s6/p4.csv',
     'D:/Projectcourse_vineet/Dataset/s6/p5.csv',
    ]


# Initialize an empty DataFrame to concatenate all data
all_data = pd.DataFrame()

# Loop through each file and read data
# Loop through each file and read data
# Loop through each file and read data
for file_path in excel_file_path:
    # Read the CSV file
    df = pd.read_csv(file_path)
    
    # Convert non-numeric data to NaN and ensure all columns are numeric
    df = df.apply(pd.to_numeric, errors='coerce')  # Convert non-numeric to NaN
    
    # Drop rows with NaN values
    df.dropna(inplace=True)
    
    # Concatenate the current file data to the main DataFrame
    all_data = pd.concat([all_data, df], ignore_index=True)




# Separate features and target variable
X = all_data.iloc[1:, 1:].values  # Skip the first row and first column
y = all_data.iloc[1:, 0].values   # Skip the first row but select the first column (target variable)


# Re-check for NaNs or Inf after cleaning and find which rows/columns contain them
# nan_mask_X = np.isnan(X)
# inf_mask_X = np.isinf(X)

# nan_mask_y = np.isnan(y)
# inf_mask_y = np.isinf(y)

# # Check for rows with NaNs or Infinities in X
# if nan_mask_X.any() or inf_mask_X.any():
#     print("Rows with NaNs or Infinities in X:")
#     print(np.where(nan_mask_X | inf_mask_X))
    
#     # Optionally, handle NaNs or Infinities
#     X = np.nan_to_num(X, nan=0.0, posinf=1e10, neginf=-1e10)  # Replace NaNs with 0, and infinities with large finite numbers

# # Check for NaNs or Infinities in y
# if nan_mask_y.any() or inf_mask_y.any():
#     print("Rows with NaNs or Infinities in y:")
#     print(np.where(nan_mask_y | inf_mask_y))
    
#     # Optionally, handle NaNs or Infinities
#     y = np.nan_to_num(y, nan=0.0, posinf=1e10, neginf=-1e10)  # Replace NaNs with 0, and infinities with large finite numbers

# # Re-check for NaNs or Inf again
# if np.any(np.isnan(X)) or np.any(np.isinf(X)):
#     raise ValueError("Cleaned input data still contains NaNs or Infinities")

# if np.any(np.isnan(y)) or np.any(np.isinf(y)):
#     raise ValueError("Cleaned target data still contains NaNs or Infinities")

# Standardize features
scaler = StandardScaler()
X = scaler.fit_transform(X)

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)


# Ensure inputs and labels are of float32 type
X_train = torch.Tensor(X_train).float()
y_train = torch.Tensor(y_train).float()
X_test = torch.Tensor(X_test).float()
y_test = torch.Tensor(y_test).float()



# Define the neural network model
class EnhancedMLP(nn.Module):
    def __init__(self):
        super(EnhancedMLP, self).__init__()
        # First fully connected layer
        self.fc1 = nn.Linear(X_train.shape[1], 128)
        self.bn1 = nn.BatchNorm1d(128)
        self.dropout1 = nn.Dropout(0.3)
        
        # Second fully connected layer
        self.fc2 = nn.Linear(128, 64)
        self.bn2 = nn.BatchNorm1d(64)
        self.dropout2 = nn.Dropout(0.3)
        
        # Third fully connected layer
        self.fc3 = nn.Linear(64, 32)
        self.bn3 = nn.BatchNorm1d(32)
        self.dropout3 = nn.Dropout(0.3)
        
        # Fourth fully connected layer
        self.fc4 = nn.Linear(32, 16)
        
        # Output layer
        self.fc5 = nn.Linear(16, 1)
        
        # Activation functions
        self.leaky_relu = nn.LeakyReLU(negative_slope=0.01)

    def forward(self, x):
        # Forward pass with batch norm, dropout, and leaky relu
        x = self.leaky_relu(self.bn1(self.fc1(x)))
        x = self.dropout1(x)
        
        x = self.leaky_relu(self.bn2(self.fc2(x)))
        x = self.dropout2(x)
        
        x = self.leaky_relu(self.bn3(self.fc3(x)))
        x = self.dropout3(x)
        
        x = self.leaky_relu(self.fc4(x))
        x = self.fc5(x)  # Output layer (no activation function for regression)
        
        return x


# Initialize the model
model = ExtendedMLP()
criterion = nn.MSELoss()  # Mean Squared Error Loss for regression
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

# Training Loop
num_epochs = 10000
train_loss_values = []
test_loss_values = []

for epoch in range(num_epochs):
    model.train()  # Set the model to training mode
    inputs = torch.Tensor(X_train)
    labels = torch.Tensor(y_train)
    optimizer.zero_grad()  # Zero the gradients
    outputs = model(inputs)  # Forward pass
    train_loss = criterion(outputs.squeeze(), labels)  # Compute loss
    
    train_loss.backward()  # Backward pass
    optimizer.step()  # Update weights

    # Store the raw training loss value (not divided yet)
    train_loss_values.append(train_loss.item())
    
    model.eval()  # Set the model to evaluation mode
    with torch.no_grad():
        test_inputs = torch.Tensor(X_test)
        test_labels = torch.Tensor(y_test)
        test_outputs = model(test_inputs)
        test_loss = criterion(test_outputs.squeeze(), test_labels)
        
        # Store the raw test loss value (not divided yet)
        test_loss_values.append(test_loss.item())

    # Print the loss every 100 epochs, divided by the number of samples
    if (epoch + 1) % 100 == 0:
        print(f'Epoch [{epoch + 1}/{num_epochs}], '
              f'Train Loss: {train_loss.item() / len(X_train):.4f}, '
              f'Test Loss: {test_loss.item() / len(X_test):.4f}')
        torch.save(model.state_dict(), 'model_weights.pth')

# Plot the training and testing loss curves
plt.figure(figsize=(12, 6))
plt.plot(train_loss_values, label='Training Loss')
plt.plot(test_loss_values, label='Testing Loss')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.title('Training and Testing Loss vs Epoch')
plt.legend()
plt.show()
