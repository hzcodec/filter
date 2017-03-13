#ifndef _SINUS_GEN_H_
#define _SINUS_GEN_H_

typedef struct {
    int   noSamples;    // number of samples
    float amplitude;    // amplitude scale factor
    float alpha;        // alpha value for low pass filter
    bool  enableNoise;  // enable noise;
    float minNoise;     // min noise level
    float maxNoise;     // max noise level
    float scaleFactor;  // scale factor of noise level
    int   ratio;        // square wave ratio in %
    int   windowSize;   // window size for average calculation
    int   slope;        // ramp slope
}Generator;

float* sinus_array(Generator *gen);
float* square_array(Generator *gen);
float* ramp_array(Generator *gen);
float* counter_array(Generator *gen);
float* power_of_2(Generator *gen);

#endif
