//
// Created by willr on 02/04/2026.
//

#ifndef PFE_PROJECT_WILLT_IO_H
#define PFE_PROJECT_WILLT_IO_H
#include "waveform.h"

// list of functions:

FILE* openFile(const char* file_input);
void extractFileData(FILE* file, WaveformSample* sample_store);
void report(const PhaseX* A_data, const PhaseX* B_data, const PhaseX* C_data);

#endif //PFE_PROJECT_WILLT_IO_H