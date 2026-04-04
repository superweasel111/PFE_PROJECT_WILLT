#include <stdio.h>
#include <math.h>
#include "waveform.h"

void clipCheck(const WaveformSample* sample_data, Phase* A_data, Phase* B_data, Phase* C_data)
{

    const float threshold = 324.9f;

    if ( fabsf(sample_data->phase_A_voltage) >= threshold) // Checks if ABSOLUTE value matches or exceeds threshold
    {
        A_data->clip_timestamps[A_data->clip_count] = sample_data->timestamp; // Append (add to index = current clip count) the current sample timestamp to the clip timestamps array
        A_data->clip_count++;
    }

    if ( fabsf(sample_data->phase_B_voltage) >= threshold)
    {
        B_data->clip_timestamps[B_data->clip_count] = sample_data->timestamp;
        B_data->clip_count++;
    }

    if ( fabsf(sample_data->phase_C_voltage) >= threshold)
    {
        C_data->clip_timestamps[C_data->clip_count] = sample_data->timestamp;
        C_data->clip_count++;
    }

}

void sampleAnalysis(const WaveformSample* sample_data, Phase* A_data, Phase* B_data, Phase* C_data)
{

    clipCheck(sample_data, A_data, B_data, C_data);

}
