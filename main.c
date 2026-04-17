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

    WaveformSample* sample_store = calloc(1, sizeof(WaveformSample)); // Allocate memory for sample store and initialise it to be zeroes
    extractFileData(file, sample_store); // Store file data into sample store
    fclose(file); // Close the file once we have extracted its data


    // PERFORM DATA ANALYSIS
    // ______________________________________________________________________________________________________________

    PhaseStore* phase_data = calloc(1, sizeof(PhaseStore));
    PhaseX* phase_A = &phase_data->PhaseA;
    PhaseX* phase_B = &phase_data->PhaseB;
    PhaseX* phase_C = &phase_data->PhaseC;

    // Iterate through each sample in the store, analysing each:
    for (int sample_index = 0; sample_index < MAX_SAMPLES; sample_index++)
    {
        const double timestamp = sample_store->timestamp[sample_index];

        printf("Attempting index %d\n", sample_index); // Debug message

        sampleAnalysis(phase_A, sample_store->phase_A_voltage[sample_index], timestamp); // Perform analysis on each phase, including voltage arguments so their respective totals may be calculated
        sampleAnalysis(phase_B, sample_store->phase_B_voltage[sample_index], timestamp);
        sampleAnalysis(phase_C, sample_store->phase_C_voltage[sample_index], timestamp);
    }
    free(sample_store); // Samples no longer needed, all data analysed. Free memory.

    // PERFORM FINAL ANALYSIS AND WRITE REPORT
    // ______________________________________________________________________________________________________________

    finalAnalysis(&phase_data->PhaseA);
    finalAnalysis(&phase_data->PhaseB);
    finalAnalysis(&phase_data->PhaseC);

    report(phase_A, phase_B, phase_C);
    free(phase_data); // Phases no longer needed, all data reported. Free memory.

    return 0;
}