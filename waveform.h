//
// Created by willr on 02/04/2026.
//

#ifndef PFE_PROJECT_WILLT_WAVEFORM_H
#define PFE_PROJECT_WILLT_WAVEFORM_H

#define MAX_SAMPLES 1000

typedef struct
{
    double timestamp[MAX_SAMPLES];
    double phase_A_voltage[MAX_SAMPLES];
    double phase_B_voltage[MAX_SAMPLES];
    double phase_C_voltage[MAX_SAMPLES];
    double line_current[MAX_SAMPLES];
    double frequency[MAX_SAMPLES];
    double power_factor[MAX_SAMPLES];
    double thd_percent[MAX_SAMPLES];
}WaveformSample;

typedef struct
{
    double max;
    double min;
    double amplitude;
    double voltage_running_total;
    double mean;
    double voltage_square_total;
    double RMS;
    int RMS_compliance;
    int clip_count;
    double clip_timestamps[MAX_SAMPLES];
}PhaseX;

typedef struct
{
    PhaseX PhaseA;
    PhaseX PhaseB;
    PhaseX PhaseC;
}PhaseStore;

// list of functions:

void sampleAnalysis(PhaseX* phase_X, double phase_X_voltage, double timestamp);
void finalAnalysis(PhaseX* phase);

#endif //PFE_PROJECT_WILLT_WAVEFORM_H

