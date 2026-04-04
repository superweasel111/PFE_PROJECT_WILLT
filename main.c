#include <stdio.h>
#include "waveform.h"

int main()
{
    extractFileData(file_input);



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