//
// Created by willr on 02/04/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"

FILE* openFile(char file_input)
{
    FILE* file = fopen(&file_input, "r"); // Open the file
    if (file == NULL)
    {
        printf("Error opening file. Does it exist?");
    }
    return file;
}

WaveformSample* extractFileData(FILE* file)
{

    WaveformSample* sample_store = malloc(sizeof(WaveformSample) * 1001); // Create sample_store to be returned at the end while allocating memory for it

    int line_index = 0;
    char current_line[256]; // A buffer to store each line from fgets()

    while (fgets(current_line, sizeof(current_line), file) != NULL) // As long as the end of the file hasn't been reached,
    {
        WaveformSample* current_sample = &sample_store[line_index];
        const int success = sscanf(current_line,
                "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                &current_sample->timestamp,
                &current_sample->phase_A_voltage,
                &current_sample->phase_B_voltage,
                &current_sample->phase_C_voltage,
                &current_sample->line_current,
                &current_sample->frequency,
                &current_sample->power_factor,
                &current_sample->thd_percent);

        // Only move to the next line index if the previous line was successfully stored
        if (success == 8)
            line_index++;
    }

    return sample_store;
}

void report(const Phase* A_data, const Phase* B_data, const Phase* C_data)
{

    // FILE *results_file = fopen("results.txt", "w"); // Create a new results.txt for writing

    printf("ANALYSIS  | PHASE A | PHASE B | PHASE C"
           "Mean      |%*lf %*lf %*lf"
           "RMS       |%*lf %*lf %*lf"
           "Amplitude |%*lf %*lf %*lf",
           28, A_data->mean, 28, B_data->mean, 28, C_data->mean,
           28, A_data->RMS, 28, B_data->RMS, 28, C_data->RMS,
           28, 0.0, 28, 0.0, 28, 0.0);

}











