// float input_features[] = { 700.96, 770.55, 754.42, 756.44, 72 };

#include <Arduino.h>
#include "svr_model.h"  // Include the SVR model header file
#include "scaling_params.h"  // Include the scaling values

float predicted_value = 0;
float input_features[num_features];  // Array to store user input features
float scaled_features[num_features]; // Array to store standardized inputs

// Function to standardize input data
void standardize(const float input[], float output[], int size) {
  for (int i = 0; i < size; i++) {
    output[i] = (input[i] - mean[i]) / std_dev[i];  // Standardization formula
  }
}

// RBF Kernel Function
float rbf_kernel(float x[], const float sv[], int size) {
  float sum = 0.0;
  for (int i = 0; i < size; i++) {
    float diff = x[i] - sv[i];
    sum += diff * diff;
  }
  return exp(-gamma_svr * sum);
}

// SVR Prediction Function
float svr_predict(float input_features[]) {
  standardize(input_features, scaled_features, num_features);
  float result = intercept;

  for (int i = 0; i < num_support_vectors; i++) {
    float kernel_value = rbf_kernel(scaled_features, support_vectors[i], num_features);
    result += dual_coefs[i] * kernel_value;
  }
  return result;
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Enter 5 feature values, separated by spaces:");
}

void loop() {
  if (Serial.available()) {
    // Read user input
    for (int i = 0; i < num_features; i++) {
      while (!Serial.available()) {
        // Wait for user input
      }
      input_features[i] = Serial.parseFloat();
    }

    // Perform SVR prediction
    predicted_value = svr_predict(input_features);

    // Print the predicted value
    Serial.print("Predicted Value: ");
    Serial.println(predicted_value);
    
    Serial.println("\nEnter new 5 feature values:");
  }
}
