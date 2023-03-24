# ADC API Design
The ADC API design in the DxCore library introduces new data structures and 
functions for configuring and reading analog values from the ADC of a 
microcontroller or similar device. The new data structure, ADCConfig, allows for 
easy configuration of various ADC parameters such as conversion mode, resolution, 
prescaler, sample delay, sample length, and sample number. Additionally, new 
functions such as analogRead(), analogReadConfig(), getAnalogReadConfig(), 
analogReadSampleDelay(), analogReadEnableSingleEnded(), analogReadEnableDifferential(), 
analogReadSampleNum(), and analogReadPrescaler() are introduced for reading and 
configuring the ADC module.

## Data Structures
### `ADCConfig`
Structure for containing all of the ADC configuration parameters:
```c
typedef struct ADCConfig_struct {
    uint8_t convMode;    // ADC conversion mode (single-ended/differential)
	uint8_t muxNeg;      // Negative pin for differential ADC conversion
	uint8_t resolution;  // ADC bit resolution
	uint8_t prescaler;   // ADC clock prescaler value
	uint8_t sampleNum;   // Number of ADC samples to accumulate
	uint8_t sampleDelay; // Delay between ADC samples in accumulation mode
	uint8_t sampleLen;   // ADC sampling time in ADC clock cycles
} ADCConfig;
```

A default instance of the struct that can be copied to get default config values:
```c
const ADCConfig ADCConfig_default = {
    .convMode = 0,
    .muxNeg = 0x16,
    .resolution = 10,
    .prescaler = ADC_DEFAULT_PRESCALER,
    .sampleNum = 0,
    .sampleDelay = 0,
    .sampleLen = 14
};
```

## Functions

### `void analogReadConfig(ADCConfig config)`
The function takes a single argument `config` of type `ADCConfig`, which contains 
the user-defined configuration settings for the adjusting the ADC module.

Usage Example:
```c
ADCConfig config = ADCConfig_default;
config.sampleNum = ADC_SAMPNUM_ACC8_gc;
config.sampleDelay = ADC_SAMPDLY_DLY10_gc;
// More config if desired...
analogReadConfig(config);
```

### `ADCConfig getAnalogReadConfig()`
The function retrieves the current configuration settings for the Analog-to-Digital 
Converter (ADC) and returns them as an `ADCConfig` structure.

Usage Example:
```c
ADCConfig currentConfig = getAnalogReadConfig();
```

### `void analogReadSampleDelay(uint8_t delay)`
Set delay in clock cycles between samples when accumulation mode is enabled. 
Valid values for `delay` are 0-15. Can be used to suppress periodic noise that 
would influence the sampling. 

Relevant register: `ADC0.CTRLD:SAMPDLY`

### `void analogReadEnableSingleEnded()`
Change ADC to single-ended mode. In single-ended mode, the ADC conversion result 
is the input voltage divided by the ADC reference voltage multiplied by a scaling 
factor. In this mode, only one voltage input needs to selected. 

Relevant register: `ADC0.CTRLA:CONVMODE`

### `void analogReadEnableDifferential(uint8_t negPin)`
Change ADC to differential mode with given negative pin. In differential mode, 
two voltage inputs are selected and the ADC conversion result is the difference 
between the two inputs divided by the ADC reference multiplied by a scaling factor. 

Relevant registers:
- `ADC0.CTRLA:CONVMODE`
- `ADC0.MUXNEG`

### `void analogReadSampleNum(uint8_t samples)`
Set the number of consecutive ADC samples to accumulate. Accumulation is disabled 
by default, when enabled multiple samples will be taken and added together before 
being returned as the ADC result. Accumulation results in the ADC result having 
a higher bit resolution and at high accumulation values results in the 
least-significant bits being dropped.

Valid values for `samples`:
- 0x0: no accumulation (`ADC_SAMPNUM_NONE_gc`)
- 0x1: 2 samples (`ADC_SAMPNUM_ACC2_gc`)
- 0x2: 4 samples (`ADC_SAMPNUM_ACC4_gc`)
- 0x3: 8 samples (`ADC_SAMPNUM_ACC8_gc`)
- 0x4: 16 samples (`ADC_SAMPNUM_ACC16_gc`)
- 0x5: 32 samples (`ADC_SAMPNUM_ACC32_gc`)
- 0x6: 64 samples (`ADC_SAMPNUM_ACC64_gc`)
- 0x7: 128 samples (`ADC_SAMPNUM_ACC128_gc`)

Relevant register: `ADC0.CTRLB:SAMPNUM`: 

### `void analogReadPrescaler(uint8_t prescaler)`
Set the prescaler value for the ADC module. The prescaler value adjusts the 
clock frequency of the ADC module, and by setting a valid prescaler value, the 
user can adjust the speed and accuracy of the ADC conversion to meet their needs.

Valid values for `prescaler`:
- 0x0: clock divided by 2 (`ADC_PRESC_DIV2_gc`)
- 0x1: clock divided by 4 (`ADC_PRESC_DIV4_gc`)
- 0x2: clock divided by 8 (`ADC_PRESC_DIV8_gc`)
- 0x3: clock divided by 12 (`ADC_PRESC_DIV12_gc`)
- 0x4: clock divided by 16 (`ADC_PRESC_DIV16_gc`)
- 0x5: clock divided by 20 (`ADC_PRESC_DIV20_gc`)
- 0x6: clock divided by 24 (`ADC_PRESC_DIV24_gc`)
- 0x7: clock divided by 28 (`ADC_PRESC_DIV28_gc`)
- 0x8: clock divided by 32 (`ADC_PRESC_DIV32_gc`)
- 0x9: clock divided by 48 (`ADC_PRESC_DIV48_gc`)
- 0xA: clock divided by 64 (`ADC_PRESC_DIV64_gc`)
- 0xB: clock divided by 96 (`ADC_PRESC_DIV96_gc`)
- 0xC: clock divided by 128 (`ADC_PRESC_DIV128_gc`)
- 0xD: clock divided by 256 (`ADC_PRESC_DIV256_gc`)

Relevant register: `ADC0.CTRLC:PRESC`