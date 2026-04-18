#include <stdio.h>
#include <math.h>
#include "waveform.h"

void sampleAnalysis(PhaseX* phase_X, const double phase_X_voltage, const double timestamp)
{
    // Track maximum and minimum values so far for amplitude calculations later:
    if (phase_X_voltage > phase_X->max) // If current voltage is larger than current maximum...
        phase_X->max = phase_X_voltage; // Set as new maximum
    if (phase_X_voltage < phase_X->min) // If current voltage is smaller than current minimum...
        phase_X->min = phase_X_voltage; // Set as new minimum

    // Clipping check:
    const float threshold = 324.9f;

    if ( fabs(phase_X_voltage) >= threshold ) // Checks if ABSOLUTE value matches or exceeds threshold
    {
        phase_X->clip_timestamps[phase_X->clip_count] = timestamp; // Append the timestamp of the current sample to the store of timestamps at which the voltage clips
        phase_X->clip_count++; // Increase the counter of instances at which the voltage clips
    }

    // Running totals:
    phase_X->voltage_running_total += phase_X_voltage;
    phase_X->voltage_square_total += phase_X_voltage * phase_X_voltage;
}

void finalAnalysis(PhaseX* phase)
{
    // Mean
    phase->mean = phase->voltage_running_total / MAX_SAMPLES;

    // RMS
    phase->RMS = sqrt( phase->voltage_square_total / MAX_SAMPLES );

    // RMS Compliance
    const double lower_threshold = 230 - (230 * 0.1);
    const double upper_threshold = 230 + (230 * 0.1);

    if (lower_threshold < phase->RMS && phase->RMS < upper_threshold)
        phase->RMS_compliance = 1;
}
