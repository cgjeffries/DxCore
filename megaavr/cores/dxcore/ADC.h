#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C"{
#endif

#if F_CPU >= 48000000
    #define ADC_DEFAULT_PRESCALER 48
#elif F_CPU >  40000000
    #define ADC_DEFAULT_PRESCALER 32
#elif F_CPU >= 36000000
    #define ADC_DEFAULT_PRESCALER 28
#elif F_CPU >  28000000
    #define ADC_DEFAULT_PRESCALER 24
#elif F_CPU >= 24000000
    #define ADC_DEFAULT_PRESCALER 20
#elif F_CPU >= 20000000
    #define ADC_DEFAULT_PRESCALER 16
#elif F_CPU >  12000000
    #define ADC_DEFAULT_PRESCALER 12
#elif F_CPU >= 8000000
    #define ADC_DEFAULT_PRESCALER 8
#elif F_CPU >= 4000000
    #define ADC_DEFAULT_PRESCALER 4
#else
    #define ADC_DEFAULT_PRESCALER 2
#endif

//////////////////////////////////////////////////////////////
//                     General ADC API                      //
//////////////////////////////////////////////////////////////

/*
Structure used for the ADC configuration
*/
typedef struct ADCConfig_struct {
    uint8_t convMode;    // 0 = single-ended, 1 = differential
    uint8_t muxNeg;      // Differential mode negative pin
    uint8_t resolution;  // ADC bit resolution
    uint16_t prescaler;   // ADC clock prescaler
    uint8_t sampleNum;   // Number of samples to accumulate - should define constants for these
    uint8_t sampleDelay; // Delay in ADC clock cycles between samples during accumulation
    uint8_t sampleLen;   // ADC sampling time in ADC clock cycles
} ADCConfig;

extern const ADCConfig ADCConfig_default;

/*
Sets the registers to fit the passed in configuration
*/
void analogReadConfig(ADCConfig config);

/*
Specify an accumulation amount
*/
void analogReadSampleNum(uint8_t numSamples);

/*
Specify the delay between samples
*/
void analogReadSampleDelay(uint8_t delay);

/*
Set the prescalaer
*/
void analogReadPrescaler(uint16_t prescaler);

/*
Enables single-ended mode
*/
void analogReadEnableSingleEnded();

/*
Enables differential mode
*/
void analogReadEnableDifferential(uint8_t negPin);

#ifdef __cplusplus
}
#endif

#endif
