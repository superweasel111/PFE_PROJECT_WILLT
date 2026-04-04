//
// Created by willr on 02/04/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"

WaveformSample* extractFileData(FILE* file)
{

    WaveformSample* sample_store = malloc(sizeof(WaveformSample) * 1000);

    int line_index = 1;
    char current_line[256];
    while (fgets(current_line, sizeof(current_line), file) != NULL && line_index < 1000)
    {
        sscanf(current_line,
                "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
                &sample_store[line_index].timestamp,
                &sample_store[line_index].phase_A_voltage,
                &sample_store[line_index].phase_B_voltage,
                &sample_store[line_index].phase_C_voltage,
                &sample_store[line_index].line_current,
                &sample_store[line_index].frequency,
                &sample_store[line_index].power_factor,
                &sample_store[line_index].thd_percent);

        line_index++;
    }

    return sample_store;
}











