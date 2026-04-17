//
// Created by willr on 02/04/2026.
//

#ifndef PFE_PROJECT_WILLT_IO_H
#define PFE_PROJECT_WILLT_IO_H
#include "waveform.h"

// list of functions:

WaveformSample* extractFileData(FILE* file, WaveformSample* sample_store);
FILE* openFile(const char* file_input);
void report(PhaseStore* phase_data);

#endif //PFE_PROJECT_WILLT_IO_H