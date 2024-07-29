#include <stdio.h>
#include <stdlib.h>

// Optimized ReLU function using bitwise operations and OpenACC
void relu(float *input, float *output, int size) {
    #pragma acc parallel loop
    for (int i = 0; i < size; i++) {
        // Using bitwise operation to avoid branching
        unsigned int mask = (*(unsigned int *)&input[i]) >> 31; // Extract sign bit
        output[i] = input[i] * (1 - mask); // Zero out negative values
    }
}

int main() {
    int size = 1000000;
    float *input = (float *) malloc(size * sizeof(float));
    float *output = (float *) malloc(size * sizeof(float));

    // Initialize input data
    for (int i = 0; i < size; i++) {
        input[i] = (float)(rand() % 2000 - 1000) / 100;
    }

    // Call the ReLU function
    relu(input, output, size);

    // Check results
    for (int i = 0; i < 10; i++) {
        printf("input[%d] = %f, output[%d] = %f\n", i, input[i], i, output[i]);
    }

    free(input);
    free(output);

    return 0;
}
