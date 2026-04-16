#include <stdio.h>
#include <stdlib.h>

#include "waveform.h"
#include "io.h"

int main(int argc, char* argv[])
{
    // OPEN THE FILE AND EXTRACT THE DATA
    // ______________________________________________________________________________________________________________

    //const char* file_input = argv[1]; // Grab the first argument from the command line as the file name

    const char* file_input = "C:\\Users\\willr\\CLionProjects\\PFE_PROJECT_WILLT\\power_quality_log.csv";
    FILE* file = openFile(file_input); // Open file if it is found

    WaveformSample *sample_store = calloc(1, sizeof(WaveformSample)); // Allocate memory for sample store and initialise it to be zeroes
    sample_store = extractFileData(file, sample_store); // Store file data into sample store

    fclose(file); // Close the file once we have extracted its data


    // PERFORM DATA ANALYSIS
    // ______________________________________________________________________________________________________________

    PhaseData* phase_data = {0}; // Initialise collection of phase data
    PhaseData* phase_data_ptr = phase_data;

    // Iterate through each sample in the store, analysing each:
    for (int sample_index = 0; sample_index < MAX_SAMPLES; sample_index++)
    {
        const double timestamp = sample_store->timestamp[sample_index];

        printf("Attempting index %d\n", sample_index); // Debug message

        sampleAnalysis(&phase_data->A, timestamp, sample_store->phase_A_voltage[sample_index]); // Perform analysis on each phase, including voltage arguments so their respective totals may be calculated
        sampleAnalysis(&phase_data->B, timestamp, sample_store->phase_B_voltage[sample_index]);
        sampleAnalysis(&phase_data->C, timestamp, sample_store->phase_C_voltage[sample_index]);
    }


    // PERFORM FINAL ANALYSIS AND WRITE REPORT
    // ______________________________________________________________________________________________________________

    finalAnalysis();

    report(A_data, B_data, C_data);

    return 0;
}