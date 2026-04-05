//
// Created by willr on 02/04/2026.
//

#ifndef PFE_PROJECT_WILLT_IO_H
#define PFE_PROJECT_WILLT_IO_H
#include "waveform.h"

// list of functions:

WaveformSample* extractFileData(FILE* file);
FILE* openFile(const char* file_input);
void report(const Phase* A_data, const Phase* B_data, const Phase* C_data);

#endif //PFE_PROJECT_WILLT_IO_H