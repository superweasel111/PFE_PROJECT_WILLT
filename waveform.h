//
// Created by willr on 02/04/2026.
//

#ifndef PFE_PROJECT_WILLT_WAVEFORM_H
#define PFE_PROJECT_WILLT_WAVEFORM_H

typedef struct{
    float timestamp;
    float phase_A_voltage;
    float phase_B_voltage;
    float phase_C_voltage;
    float line_current;
    float frequency;
    float power_factor;
    float thd_percent;
}WaveformSample;

typedef struct
{
    float voltage_running_total;
    float mean;
    float voltage_square_total;
    float RMS;
    float RMS_compliance;
    int clip_count;
    float clip_timestamps[];
}Phase;

// list of functions:

void sampleAnalysis(const WaveformSample* sample_data, Phase* A_data, Phase* B_data, Phase* C_data);
void clipCheck(const WaveformSample* sample_data, Phase* A_data, Phase* B_data, Phase* C_data);

#endif //PFE_PROJECT_WILLT_WAVEFORM_H

