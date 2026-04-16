#include <stdio.h>
#include <stdlib.h>

#include "waveform.h"
#include "io.h"

int main(int argc, char* argv[])
{
    //const char* file_input = argv[1]; // Grab the first argument from the command line as the file name

    const char* file_input = "C:\\Users\\willr\\CLionProjects\\PFE_PROJECT_WILLT\\power_quality_log.csv";
    FILE* file = openFile(file_input); // Open file if it is found

    WaveformSample* sample_store = {0};
    sample_store = extractFileData(file, sample_store);


    fclose(file); // Close the file once we have extracted its data

    // Initialise Phase structs for each phase and assign pointers for later editing
    Phase A = {0};
    Phase B = {0};
    Phase C = {0};

    Phase* A_data = &A;
    Phase* B_data = &B;
    Phase* C_data = &C;

    // Iterate through each sample in the store, analysing each:
    for (int sample_index = 0; sample_index < MAX_SAMPLES; sample_index++)
    {
        const WaveformSample* sample_data = &sample_store[sample_index]; // Make a pointer referencing the current sample as an address in the array
        const double timestamp = sample_data->timestamp[sample_index];

        printf("Attempting index %d\n", sample_index); // Debug message

        sampleAnalysis(A_data, timestamp, sample_data->phase_A_voltage); // Analyse the current sample, providing an argument for each phase so their respective totals may be calculated
        sampleAnalysis(B_data, timestamp, sample_data->phase_B_voltage);
        sampleAnalysis(C_data, timestamp, sample_data->phase_C_voltage);
    }

    finalAnalysis(A_data);
    finalAnalysis(B_data);
    finalAnalysis(C_data);

    report(A_data, B_data, C_data);

    free(sample_store);
    return 0;
}