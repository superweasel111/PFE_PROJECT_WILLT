#include <stdio.h>
#include "waveform.h"
#include "io.h"

int main(int argc, const char argv[])
{
    const char* file_input = &argv[1]; // Grab the first argument from the command line as the file name
    FILE* file = openFile(*file_input);

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
        const WaveformSample* sample_data = &sample_store[sample_index]; // Make a pointer referencing the current sample as an address in the array
        sampleAnalysis(sample_data, A_data, sample_data->phase_A_voltage); // Analyse this current sample, providing an argument for each phase so their respective totals may be calculated
        sampleAnalysis(sample_data, B_data, sample_data->phase_B_voltage);
        sampleAnalysis(sample_data, C_data, sample_data->phase_C_voltage);
    }

    finalAnalysis(A_data);
    finalAnalysis(B_data);
    finalAnalysis(C_data);

    report();

    return 0;
}