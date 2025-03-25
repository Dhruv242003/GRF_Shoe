#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#include "model.h"  // Include the converted model.h file

// Standardization Parameters
const float mean[5] = { 802.775, 768.897, 754.557, 758.944, 64.894 };
const float std_dev[5] = { 14.868, 4.123, 2.141, 3.135, 6.938 };

// Global variables used for TensorFlow Lite (Micro)
tflite::MicroErrorReporter tflErrorReporter;
tflite::AllOpsResolver tflOpsResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

// Define tensor arena size (adjust based on model requirements)
constexpr int tensorArenaSize = 8 * 1024;
alignas(16) byte tensorArena[tensorArenaSize];

// Define label for output (assumes single output Fz)
const char* LABELS[] = { "Fz" };
#define NUM_LABELS (sizeof(LABELS) / sizeof(LABELS[0]))


// Input Features (Raw values before standardization)
// float input_parameters[] = {850.87 , 788.89,	783.55,	790.75,	66};
float scaled_features[5];

void standardize(float input[], float output[], int size) {
  for (int i = 0; i < size; i++) {
    output[i] = (input[i] - mean[i]) / std_dev[i];
  }
}


void DL_setup() {
  tflModel = tflite::GetModel(model);
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1)
      ;
  }

  // Initialize TFLite interpreter
  tflInterpreter = new tflite::MicroInterpreter(
    tflModel, tflOpsResolver, tensorArena, tensorArenaSize, &tflErrorReporter);

  // Allocate tensors
  if (tflInterpreter->AllocateTensors() != kTfLiteOk) {
    Serial.println("Tensor allocation failed!");
    while (1)
      ;
  }

  // Get pointers to input/output tensors
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);
}


float predictDL(){
  memcpy(tflInputTensor->data.f, scaled_features, sizeof(scaled_features));

    // Invoke model inference
    TfLiteStatus invokeStatus = tflInterpreter->Invoke();
    if (invokeStatus != kTfLiteOk) {
        Serial.println("Invoke failed!");
        while (1);
    }
  
  return tflOutputTensor->data.f[0];
}


