#include <TensorFlowLite.h>
#include "model_data.h"  // Include the TFLite model converted to a C array
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

// TensorFlow Lite memory allocation
const int tensor_arena_size = 20 * 1024;  // Adjust based on model size
uint8_t tensor_arena[tensor_arena_size];

tflite::MicroInterpreter* interpreter;
tflite::MicroErrorReporter error_reporter;


// GIve the model name here
model_tflite = HundredEpochs_model_tflite;


void setup() {
    Serial.begin(115200);
    delay(2000); // Allow time for serial connection

    Serial.println("Initializing TensorFlow Lite Model...");

    // Load the model
    const tflite::Model* model = tflite::GetModel(model_tflite);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        Serial.println("Model schema version mismatch!");
        while (1);
    }

    // Set up the operator resolver
    static tflite::AllOpsResolver resolver;

    // Create an interpreter
    static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, tensor_arena_size, &error_reporter);
    interpreter = &static_interpreter;

    // Allocate memory for tensors
    if (interpreter->AllocateTensors() != kTfLiteOk) {
        Serial.println("Tensor allocation failed!");
        while (1);
    }

    Serial.println("Model successfully loaded!");
}

void loop() {
    Serial.println("\nRunning Inference...");

    // Example input data (Modify these values based on real sensor data)
    float input_data[5] = {0.5, 0.6, 0.7, 0.8, 70.0};  // Example: (s1, s2, s3, s4, Weight)
    float* input = interpreter->input(0)->data.f;

    // Copy input values to tensor
    for (int i = 0; i < 5; i++) {
        input[i] = input_data[i];
    }

    // Run inference
    if (interpreter->Invoke() != kTfLiteOk) {
        Serial.println("Error running inference!");
        return;
    }

    // Get output tensor (Predicted GRF)
    float* output = interpreter->output(0)->data.f;

    // Print the estimated GRF value
    Serial.print("Predicted GRF: ");
    Serial.println(output[0]);

    delay(2000);  // Wait before the next inference
}
