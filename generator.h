#ifndef _SINUS_GEN_H_
#define _SINUS_GEN_H_

typedef struct {
    int   noSamples;    // number of samples
    float amplitude;    // amplitude scale factor
    bool  enableNoise;  // enable noise;
    float minNoise;     // min noise level
    float maxNoise;     // max noise level
    float scaleFactor;  // scale factor of noise level
    int   dutyCycle;    // duty cycle square wave in %
}Generator;

float* sinus_array(Generator *gen);
float* square_array(Generator *gen);

#endif
