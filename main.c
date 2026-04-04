#include <stdio.h>
#include "waveform.h"
#include "io.h"

int main(int argc, char* argv[])
{
    const char* file_input = argv[0]; // Grab the first argument from the command line as the file name

    const FILE* file = fopen(file_input, "r"); // Open the file
    if (file == NULL)
    {
        printf("Error opening file. Does it exist?");
        return 404;
    }

    const WaveformSample* sample_store = extractFileData(file);

    // Initialise Phase structs for each phase and assign pointers for later editing
    Phase A = {0,0,0,0,0,0};
    Phase B = {0,0,0,0,0,0};
    Phase C = {0,0,0,0,0,0};

    Phase* A_data = &A;
    Phase* B_data = &B;
    Phase* C_data = &C;

    // Iterate through each sample in the store, analysing each:
    for (int sample_index = 0; sample_index < 1001; sample_index++)
    {
        const WaveformSample* sample_data = &sample_store[sample_index]; // Make a pointer referencing the current sample frame as an address in the array
        sampleAnalysis(sample_data, A_data, B_data, C_data);
    }

    finalAnalysis();

    report();

    return 0;
}