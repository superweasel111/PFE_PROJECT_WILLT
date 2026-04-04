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

    WaveformSample* sample_store = malloc(sizeof(WaveformSample) * 1000);

    int line_index = 0;
    char current_line[256];

    fgets(current_line, sizeof(current_line), file); // Skip header
    while (fgets(current_line, sizeof(current_line), file) != NULL)
    {
        WaveformSample* current_sample = &sample_store[line_index];
        sscanf(current_line,
                "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                &current_sample->timestamp,
                &current_sample->phase_A_voltage,
                &current_sample->phase_B_voltage,
                &current_sample->phase_C_voltage,
                &current_sample->line_current,
                &current_sample->frequency,
                &current_sample->power_factor,
                &current_sample->thd_percent);

        line_index++;
    }

    return sample_store;
}











