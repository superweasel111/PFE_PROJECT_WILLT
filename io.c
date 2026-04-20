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
        printf("Error opening file. Does it exist?\n");
        printf("Program exit with code %d\n", ERR_FILE_NOT_FOUND);
        exit(ERR_FILE_NOT_FOUND);
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

static void printClips(FILE* file, const PhaseX* phase)
{
    for (int i = 0; i < phase->clip_count; i++)
    {
        fprintf(file, "%lf ", phase->clip_timestamps[i]);
    }
    fprintf(file, "\n"); // Empty line
}

static void phaseReport(FILE* file, const PhaseX* phase_data, const char phase_ID)
{
    char* compliance_str = (phase_data->RMS_compliance == 1 ? "was" : "was not");

    fprintf(file, "Phase %c %s RMS compliant.\n", phase_ID, compliance_str);
    fprintf(file, "Phase %c clipped %d times, at the following timestamps:\n", phase_ID, phase_data->clip_count);
    printClips(file, phase_data);
    fprintf(file, "\n"); // Empty line
}

void report(const PhaseX* A_data, const PhaseX* B_data, const PhaseX* C_data)
{
    FILE* f = fopen("results.txt", "w"); // Create a new results.txt for writing

    // Formatting preparations
    const int width = 18;

    fprintf(f, "%*s | %*s | %*s | %*s | \n", width, "ANALYSIS", width, "PHASE A", width, "PHASE B", width, "PHASE C"); // Headers
    fprintf(f, "%*s | %*lf | %*lf | %*lf |\n", width, "Amplitude", width, A_data->amplitude, width, B_data->amplitude, width, C_data->amplitude); // Amplitude
    fprintf(f, "%*s | %*lf | %*lf | %*lf |\n", width, "Mean (DC offset)", width, A_data->mean, width, B_data->mean, width, C_data->mean); // Mean
    fprintf(f, "%*s | %*lf | %*lf | %*lf |\n", width, "RMS", width, A_data->RMS, width, B_data->RMS, width, C_data->RMS); // RMS
    fprintf(f, "\n"); // Empty line
    phaseReport(f, A_data, 'A');
    phaseReport(f, B_data, 'B');
    phaseReport(f, C_data, 'C');

    fclose(f);
}











