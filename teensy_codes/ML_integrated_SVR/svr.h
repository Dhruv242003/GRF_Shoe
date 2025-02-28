float predicted_value = 0;
float input_features[num_features];
float scaled_features[num_features];  





void standardize(float input[], float output[], int size) {
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
  float result = intercept;

  for (int i = 0; i < num_support_vectors; i++) {
    // Use SCALED features in RBF kernel
    float kernel_value = rbf_kernel(input_features, support_vectors[i], num_features);
    result += dual_coefs[i] * kernel_value;
  }

  return result;
}

