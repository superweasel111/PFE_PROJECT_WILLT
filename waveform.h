//
// Created by willr on 02/04/2026.
//

#ifndef PFE_PROJECT_WILLT_WAVEFORM_H
#define PFE_PROJECT_WILLT_WAVEFORM_H

typedef struct{
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
}WaveformSample;

typedef struct
{
    double voltage_running_total;
    double mean;
    double voltage_square_total;
    double RMS;
    double RMS_compliance;
    int clip_count;
    double clip_timestamps[];
}Phase;

// list of functions:

void sampleAnalysis(const WaveformSample* sample_data, Phase* X_data, double phase_X_voltage);

#endif //PFE_PROJECT_WILLT_WAVEFORM_H

