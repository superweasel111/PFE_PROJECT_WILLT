//
// Created by willr on 02/04/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"

FILE* openFile(const char* file_input)
{
    FILE* file = fopen(file_input, "r"); // Open the file
    if (file == NULL)
    {
        printf("Error opening file. Does it exist?");
        exit(404);
    }
    return file;
}

void extractFileData(FILE* file, WaveformSample* sample_store)
{

    int line_index = 0;
    char current_line[256]; // A buffer to store each line from fgets()

    fgets(current_line, sizeof(current_line), file); // Skip header
    while (fgets(current_line, sizeof(current_line), file) != NULL) // As long as the end of the file hasn't been reached,
    {
        sscanf(current_line,
                "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                &sample_store->timestamp[line_index],
                &sample_store->phase_A_voltage[line_index],
                &sample_store->phase_B_voltage[line_index],
                &sample_store->phase_C_voltage[line_index],
                &sample_store->line_current[line_index],
                &sample_store->frequency[line_index],
                &sample_store->power_factor[line_index],
                &sample_store->thd_percent[line_index]);

        line_index++;
    }
}

void report(const PhaseX* A_data, const PhaseX* B_data, const PhaseX* C_data)
{
    FILE *results_file = fopen("results.txt", "w"); // Create a new results.txt for writing

    const int width = 14;
    fprintf(results_file,
        "ANALYSIS  |       PHASE A |        PHASE B |        PHASE C\n"
        "Mean      |%*lf | %*lf | %*lf\n"
        "RMS       |%*lf | %*lf | %*lf\n"
        "Amplitude |%*lf | %*lf | %*lf",
        width, A_data->mean, width, B_data->mean, width, C_data->mean,
        width, A_data->RMS, width, B_data->RMS, width, C_data->RMS,
        width, 0.0, width, 0.0, width, 0.0);

    fclose(results_file);
}











