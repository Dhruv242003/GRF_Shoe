// Linear Regression Model Deployment on Teensy 4.1
#include <Arduino.h>

// Define model parameters (Replace with actual trained values)
float coefficients[] = { -51.24390447, -26.97226867, 58.29750692, -78.83222018, -15.7695863 };  // Example for multiple features
float intercept = -333.4212807405909;                                                           // Intercept value

// Standardization parameters from Python
float mean[] = { 800.93105253, 769.04597102, 755.89004629, 761.82081103, 68.2129201 };  // Replace with actual values
float std_dev[] = { 14.93579566, 3.36180796, 2.34004597, 5.35692161, 4.91855033 };      // Renamed from std[] to std_dev[]

// Function to standardize input
void standardize(float input[], float output[], int size) {
  for (int i = 0; i < size; i++) {
    output[i] = (input[i] - mean[i]) / std_dev[i];  // Use std_dev instead of std
  }
}

// Function to predict output
float predict(float scaled_input[], int size) {
  float result = intercept;
  for (int i = 0; i < size; i++) {
    result += scaled_input[i] * coefficients[i];
  }
  return result;
}

void setup() {
  Serial.begin(9600);
  delay(2000);

  // Example input (replace with real sensor data)
  float input_features[] = { 795.96, 770.55, 754.42, 756.44, 72 };
  // float input_features_scaled[] = { -0.29421751, 0.33762703, -0.44295669, -0.99575061, 0.80231661 };  // Example input values
  int num_features = sizeof(coefficients) / sizeof(coefficients[0]);

  float scaled_data[num_features];
  standardize(input_features, scaled_data, num_features);  // Fixed input variable name

  float result = predict(scaled_data, num_features);

  // Print Predicted Value
  Serial.print("Predicted Value: ");
  Serial.println(result);
}

void loop() {
  // You can continuously read sensor data and predict values in the loop
}
