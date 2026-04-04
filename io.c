//
// Created by willr on 02/04/2026.
//
#include "io.h"
#include "waveform.h"

WaveformSample grabRow(int line_index)
{



}


void extractFileData(const char file_input)
{

    WaveformSample sample_store[1000];

    // Iterate through all 1000 lines, storing each:
    for (int line_index = 0; line_index < 1000; line_index++)
    {
        sample_store[line_index] = grabRow(line_index);
    }
}
