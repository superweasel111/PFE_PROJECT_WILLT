#include <stdio.h>
#include <math.h>
#include "waveform.h"

void sampleAnalysis(PhaseX* phase, const double timestamp, const double phase_X_voltage)
{

    // Clipping check:
    const float threshold = 324.9f;

    if ( fabs(phase_X_voltage) >= threshold ) // Checks if ABSOLUTE value matches or exceeds threshold
    {
        phase->clip_timestamps[phase->clip_count] = timestamp; // Append the timestamp of the current sample to the store of timestamps at which the voltage clips
        phase->clip_count++; // Increase the counter of instances at which the voltage clips
    }

    // Running totals:
    phase ->voltage_running_total += phase_X_voltage;
    X_data->voltage_square_total += phase_X_voltage * phase_X_voltage;
}

void finalAnalysis(Phase* X_data)
{
    X_data->mean = X_data->voltage_running_total / MAX_SAMPLES;
    X_data->RMS = sqrt( X_data->voltage_square_total );

    if ( 207 < X_data->RMS && X_data->RMS < 253 )
        X_data->RMS_compliance = 1;
    else
        X_data->RMS_compliance = 0;
}
