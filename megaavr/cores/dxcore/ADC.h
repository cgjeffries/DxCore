/*
This header file is based on Josh Zimmerling's ADC.h header file
https://github.com/jnbrauer/SER401-2022-Group39-Documentation/blob/main/ADC/ADC.h

Also, this file will only use parts of Josh's header file for MALS-98 only.
*/ 

#ifndef ADC_H
#define ADC_H

#include <stdint.h>

typedef struct ADCConfig_struct {
    uint8_t convMode;    // 0 = single-ended, 1 = differential
    uint8_t muxNeg;      // Differential mode negative pin
    uint8_t resolution;  // ADC bit resolution
    uint8_t prescaler;   // ADC clock prescaler
    uint8_t sampleNum;   // Number of samples to accumulate - should define constants for these
    uint8_t sampleDelay; // Delay in ADC clock cycles between samples during accumulation
    uint8_t sampleLen;   // ADC sampling time in ADC clock cycles
} ADCConfig;

/*
Specify the delay between samples
*/
void analogReadSampleDelay(uint8_t delay);

#endif