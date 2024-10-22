import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor, GradientBoostingRegressor
from sklearn.svm import SVR
from sklearn.metrics import mean_squared_error
import tensorflow as tf

# Load the dataset (Assume 'combinedResult.csv' is saved)
data = pd.read_csv('combinedResult.csv')

# Step 1: Prepare the Data
X = data[['s1', 's2', 's3', 's4', 's', 'AccX', 'AccY', 'AccZ', 'GyroX', 'GyroY', 'GyroZ']].values  # Input features
Y = data[['Fx', 'Fy', 'Fz']].values  # Output labels

# Step 2: Split the Data into Training and Test sets (80% training, 20% testing)
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, random_state=42)

# Step 3: Standardize the features (Recommended for neural networks and SVR)
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)

# Utility function to evaluate models
def evaluate_model(model, X_test, Y_test):
    Y_pred = model.predict(X_test)
    mseFx = mean_squared_error(Y_test[:, 0], Y_pred[:, 0])
    mseFy = mean_squared_error(Y_test[:, 1], Y_pred[:, 1])
    mseFz = mean_squared_error(Y_test[:, 2], Y_pred[:, 2])
    
    print(f'MSE for Fx: {mseFx:.4f}')
    print(f'MSE for Fy: {mseFy:.4f}')
    print(f'MSE for Fz: {mseFz:.4f}')

# 1. Linear Regression Model
print("\n--- Linear Regression ---")
linear_model = LinearRegression()
linear_model.fit(X_train, Y_train)
evaluate_model(linear_model, X_test, Y_test)

# 2. Random Forest Model
print("\n--- Random Forest Regressor ---")
rf_model = RandomForestRegressor(n_estimators=100, random_state=42)
rf_model.fit(X_train, Y_train)
evaluate_model(rf_model, X_test, Y_test)

# 3. Gradient Boosting Model
print("\n--- Gradient Boosting Regressor ---")
gb_model = GradientBoostingRegressor(n_estimators=100, random_state=42)
gb_model.fit(X_train, Y_train)
evaluate_model(gb_model, X_test, Y_test)

# 4. Support Vector Regressor (SVR)
print("\n--- Support Vector Regressor (SVR) ---")
svr_model = SVR(kernel='rbf')
svr_model.fit(X_train_scaled, Y_train)  # Use scaled data for SVR
evaluate_model(svr_model, X_test_scaled, Y_test)

# 5. Neural Network (Deep Learning) using TensorFlow/Keras
print("\n--- Neural Network (Deep Learning) ---")
# Define a Sequential Model
nn_model = tf.keras.models.Sequential([
    tf.keras.layers.Dense(64, activation='relu', input_shape=(X_train.shape[1],)),
    tf.keras.layers.Dense(64, activation='relu'),
    tf.keras.layers.Dense(3)  # Output layer for Fx, Fy, Fz
])

# Compile the model
nn_model.compile(optimizer='adam', loss='mse')

# Train the model
nn_model.fit(X_train_scaled, Y_train, epochs=50, batch_size=32, validation_data=(X_test_scaled, Y_test), verbose=1)

# Predict and evaluate the neural network
Y_pred_nn = nn_model.predict(X_test_scaled)
mseFx_nn = mean_squared_error(Y_test[:, 0], Y_pred_nn[:, 0])
mseFy_nn = mean_squared_error(Y_test[:, 1], Y_pred_nn[:, 1])
mseFz_nn = mean_squared_error(Y_test[:, 2], Y_pred_nn[:, 2])

print(f'MSE for Fx (NN): {mseFx_nn:.4f}')
print(f'MSE for Fy (NN): {mseFy_nn:.4f}')
print(f'MSE for Fz (NN): {mseFz_nn:.4f}')
