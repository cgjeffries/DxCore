# ADC Sample Delay Test Case
This test case demonstrates changing the usage of analogReadEnableDifferential 
and demonstrates the output to serial monitor.

# Notes
DxCore Refrence Voltage modes at `megaavr\extras\Ref_Analog.md`
| AVR Dx/Ex-series (all)                  | Voltage | Minimum Vdd | Mode # |
|-----------------------------------------|---------|-------------|--------|
| `VDD` (default 1.024V)                  | Vcc/Vdd |             |      5 |
| `INTERNAL1V024`                         | 1.024 V |      2.5* V |      0 |
| `INTERNAL2V048`                         | 2.048 V |      2.5  V |      1 |
| `INTERNAL4V096`                         | 4.096 V |      4.55 V |      2 |
| `INTERNAL2V500`                         | 2.500 V |      2.7  V |      3 |
| `INTERNAL4V1` (alias of INTERNAL4V096)  | 4.006 V |      4.55 V |      2 |
| `EXTERNAL`                              | VREF pin|        VREF |      6 |
 * `EXTERNAL` -> VREF pin -> pin (PD7)
 * VREF - Voltage Reference (pg 198 Data Sheet)
 
 The DAC Output Can *ONLY* Be Used as Input to the ADC Positive Input. (pg 508)