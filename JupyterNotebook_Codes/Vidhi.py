import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from xgboost import XGBRegressor
from sklearn.ensemble import RandomForestRegressor
from sklearn.svm import SVR
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, mean_absolute_error
import optuna
import matplotlib.pyplot as plt

# Load datasets (replace with actual file paths or dataset loading logic)
file_paths = [
    "/teamspace/studios/this_studio/fnn - arp_fnn.csv",
    "/teamspace/studios/this_studio/fnn - dharmesh_fnn.csv",
    "/teamspace/studios/this_studio/fnn - prassaana_fnn.csv",
    "/teamspace/studios/this_studio/fnn - rnk_fnn.csv",
    "/teamspace/studios/this_studio/fnn - ronak_fnn.csv",
    "/teamspace/studios/this_studio/fnn - dhruv_fnn (1).csv"
]

datasets = [pd.read_csv(path) for path in file_paths]
dataset_names = ["Arp Dataset", "Dharmesh Dataset", "Prassaana Dataset", "Rnk Dataset", "Ronak Dataset", "Dhruv Dataset"]

# Define features and target
input_features = ['s1', 's2', 's3', 's4']  # Replace with actual feature names
target_feature = 'Fz'  # Replace with actual target name

# Define a custom regression accuracy metric.
# This computes: 100 * (1 - (sum(|error|) / sum(|true|)))
def regression_accuracy(y_true, y_pred):
    denominator = np.sum(np.abs(y_true))
    # Avoid division by zero
    if denominator < 1e-10:
        return 0.0
    return 100 * (1 - np.sum(np.abs(y_true - y_pred)) / denominator)

# Function to perform hyperparameter tuning for XGBoost
def tune_hyperparameters(X_train, y_train, X_val, y_val):
    def objective(trial):
        params = {
            "n_estimators": trial.suggest_int("n_estimators", 100, 1000),
            "learning_rate": trial.suggest_float("learning_rate", 0.01, 0.2),
            "max_depth": trial.suggest_int("max_depth", 3, 10),
            "subsample": trial.suggest_float("subsample", 0.5, 1.0),
            "colsample_bytree": trial.suggest_float("colsample_bytree", 0.5, 1.0),
            "reg_alpha": trial.suggest_float("reg_alpha", 0.0, 1.0),
            "reg_lambda": trial.suggest_float("reg_lambda", 0.0, 1.0),
        }

        model = XGBRegressor(**params)
        model.fit(X_train, y_train, eval_set=[(X_val, y_val)], verbose=False)
        y_pred_val = model.predict(X_val)
        rmse = np.sqrt(mean_squared_error(y_val, y_pred_val))
        return rmse

    study = optuna.create_study(direction="minimize")
    study.optimize(objective, n_trials=50)
    return study.best_params

# Function to train and evaluate models
def train_and_evaluate(train_datasets, test_dataset, dataset_name):
    # Combine all training datasets
    train_data = pd.concat(train_datasets)

    # Normalize data
    scaler = MinMaxScaler()
    X_train = scaler.fit_transform(train_data[input_features])
    y_train = train_data[target_feature].values

    X_test = scaler.transform(test_dataset[input_features])
    y_test = test_dataset[target_feature].values

    # Split training data for hyperparameter tuning
    X_train_split, X_val, y_train_split, y_val = train_test_split(
        X_train, y_train, test_size=0.2, random_state=42
    )

    # Hyperparameter tuning for XGBoost
    best_params = tune_hyperparameters(X_train_split, y_train_split, X_val, y_val)

    # Train final XGBoost model
    xgb_model = XGBRegressor(**best_params)
    xgb_model.fit(X_train, y_train, eval_set=[(X_val, y_val)], verbose=False)
    y_pred_test_xgb = xgb_model.predict(X_test)
    rmse_xgb = np.sqrt(mean_squared_error(y_test, y_pred_test_xgb))
    mae_xgb = mean_absolute_error(y_test, y_pred_test_xgb)
    acc_xgb = regression_accuracy(y_test, y_pred_test_xgb)

    # Train Random Forest model
    rf_model = RandomForestRegressor(n_estimators=100, random_state=42)
    rf_model.fit(X_train, y_train)
    y_pred_test_rf = rf_model.predict(X_test)
    rmse_rf = np.sqrt(mean_squared_error(y_test, y_pred_test_rf))
    mae_rf = mean_absolute_error(y_test, y_pred_test_rf)
    acc_rf = regression_accuracy(y_test, y_pred_test_rf)

    # Train SVR model
    svr_model = SVR(kernel='rbf')
    svr_model.fit(X_train, y_train)
    y_pred_test_svr = svr_model.predict(X_test)
    rmse_svr = np.sqrt(mean_squared_error(y_test, y_pred_test_svr))
    mae_svr = mean_absolute_error(y_test, y_pred_test_svr)
    acc_svr = regression_accuracy(y_test, y_pred_test_svr)

    # Train Linear Regression model
    lr_model = LinearRegression()
    lr_model.fit(X_train, y_train)
    y_pred_test_lr = lr_model.predict(X_test)
    rmse_lr = np.sqrt(mean_squared_error(y_test, y_pred_test_lr))
    mae_lr = mean_absolute_error(y_test, y_pred_test_lr)
    acc_lr = regression_accuracy(y_test, y_pred_test_lr)

    return {
        "Dataset": dataset_name,
        # XGBoost
        "XGBoost RMSE": rmse_xgb,
        "XGBoost MAE": mae_xgb,
        "XGBoost Accuracy (%)": acc_xgb,
        # Random Forest
        "Random Forest RMSE": rmse_rf,
        "Random Forest MAE": mae_rf,
        "Random Forest Accuracy (%)": acc_rf,
        # SVR
        "SVR RMSE": rmse_svr,
        "SVR MAE": mae_svr,
        "SVR Accuracy (%)": acc_svr,
        # Linear Regression
        "Linear Regression RMSE": rmse_lr,
        "Linear Regression MAE": mae_lr,
        "Linear Regression Accuracy (%)": acc_lr,
        # For plotting
        "y_test": y_test,
        "y_pred_xgb": y_pred_test_xgb,
    }

# Cross-validation across datasets
results = []
for i in range(len(datasets)):
    print(f"Testing on {dataset_names[i]}")
    test_dataset = datasets[i]
    train_datasets = [datasets[j] for j in range(len(datasets)) if j != i]

    result = train_and_evaluate(train_datasets, test_dataset, dataset_names[i])
    results.append(result)

# Visualization of predictions vs. true values for XGBoost
for result in results:
    plt.figure(figsize=(10, 6))
    plt.plot(result["y_test"], label="True Values", color="blue")
    plt.plot(result["y_pred_xgb"], label="Predicted Values (XGBoost)", color="orange")
    plt.title(f"Performance on {result['Dataset']}")
    plt.xlabel("Sample Index")
    plt.ylabel("Target Value")
    plt.legend()
    plt.show()

# Summary of metrics: we now include accuracy (as defined via our custom regression accuracy)
metrics_df = pd.DataFrame([{
    "Dataset": r["Dataset"],
    "XGBoost RMSE": r["XGBoost RMSE"],
    "XGBoost Accuracy (%)": r["XGBoost Accuracy (%)"],
    "Random Forest RMSE": r["Random Forest RMSE"],
    "Random Forest Accuracy (%)": r["Random Forest Accuracy (%)"],
    "SVR RMSE": r["SVR RMSE"],
    "SVR Accuracy (%)": r["SVR Accuracy (%)"],
    "Linear Regression RMSE": r["Linear Regression RMSE"],
    "Linear Regression Accuracy (%)": r["Linear Regression Accuracy (%)"]
} for r in results])

print("\n=== Model Comparison (RMSE & Accuracy %) ===")
print(metrics_df)

# Plot RMSE comparison
metrics_df.plot(x="Dataset", y=["XGBoost RMSE", "Random Forest RMSE", "SVR RMSE", "Linear Regression RMSE"],
                kind="bar", figsize=(12, 6), title="RMSE Comparison Across Datasets")
plt.ylabel("RMSE")
plt.show()

# Plot Accuracy comparison
metrics_df.plot(x="Dataset", y=["XGBoost Accuracy (%)", "Random Forest Accuracy (%)",
                                 "SVR Accuracy (%)", "Linear Regression Accuracy (%)"],
                kind="bar", figsize=(12, 6), title="Accuracy (%) Comparison Across Datasets")
plt.ylabel("Accuracy (%)")
plt.ylim(0, 100)
plt.show()
