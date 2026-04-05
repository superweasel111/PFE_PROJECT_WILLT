#include <stdio.h>
#include <math.h>
#include "waveform.h"

void sampleAnalysis(const WaveformSample* sample_data, Phase* X_data, double phase_X_voltage)
{

    // Clipping check:
    const float threshold = 324.9f;

    if ( fabs(phase_X_voltage) >= threshold ) // Checks if ABSOLUTE value matches or exceeds threshold
    {
        X_data->clip_timestamps[X_data->clip_count] = sample_data->timestamp; // Append (add to index = current clip count) the current sample's timestamp to the clip timestamps array
        X_data->clip_count++;
    }

    // Running totals:
    X_data->voltage_running_total += phase_X_voltage;
    X_data->voltage_square_total += phase_X_voltage * phase_X_voltage;

}

void finalAnalysis(Phase* X_data)
{

    X_data->mean = X_data->voltage_running_total / 1000;
    X_data->RMS = sqrt( X_data->voltage_square_total );

    if ( 207 < X_data->RMS && X_data->RMS < 253 )
        X_data->RMS_compliance = 1;
    else
        X_data->RMS_compliance = 0;

}
