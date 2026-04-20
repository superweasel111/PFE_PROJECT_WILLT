#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "waveform.h"
#include "io.h"

int main(const int argc, char* argv[])
{
    const clock_t start_time = clock();

    // If there are more or less than 2 arguments, the program provides proper usage
    if (argc != 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        exit(ERR_INVALID_USAGE);
    }

    // OPEN THE FILE AND EXTRACT THE DATA
    // ______________________________________________________________________________________________________________

    const char* file_input = argv[1]; // Grab the first argument from the command line as the file name

    printf("Opening file...");
    FILE* file = openFile(file_input); // Open file if it is found

    WaveformSample* sample_store = calloc(1, sizeof(WaveformSample)); // Allocate memory for sample store and initialise it to be zeroes

    printf("Extracting data...");
    extractFileData(file, sample_store); // Store file data into sample store
    fclose(file); // Close the file once we have extracted its data


    // PERFORM DATA ANALYSIS
    // ______________________________________________________________________________________________________________

    PhaseStore* phase_data = calloc(1, sizeof(PhaseStore));
    PhaseX* phase_A = &phase_data->PhaseA;
    PhaseX* phase_B = &phase_data->PhaseB;
    PhaseX* phase_C = &phase_data->PhaseC;

    printf("Performing data analysis...");
    // Iterate through each sample in the store, analysing each:
    for (int sample_index = 0; sample_index < MAX_SAMPLES; sample_index++)
    {
        const double timestamp = sample_store->timestamp[sample_index];

        sampleAnalysis(phase_A, sample_store->phase_A_voltage[sample_index], timestamp); // Perform analysis on each phase, including voltage arguments so their respective totals may be calculated
        sampleAnalysis(phase_B, sample_store->phase_B_voltage[sample_index], timestamp);
        sampleAnalysis(phase_C, sample_store->phase_C_voltage[sample_index], timestamp);
    }
    free(sample_store); // Samples no longer needed, all data analysed. Free memory.

    // PERFORM FINAL ANALYSIS AND WRITE REPORT
    // ______________________________________________________________________________________________________________

    printf("Resolving phase data...");
    finalAnalysis(phase_A);
    finalAnalysis(phase_B);
    finalAnalysis(phase_C);

    printf("Writing results.txt");
    report(phase_A, phase_B, phase_C);
    free(phase_data); // Phases no longer needed, all data reported. Free memory.

    const clock_t end_time = clock();
    const double program_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Done! Program complete in %f seconds.\n", program_time);

    return 0;
}