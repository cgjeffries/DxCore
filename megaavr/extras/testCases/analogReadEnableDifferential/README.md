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
 
## Instructions
1. Connect signal generator with DC input set to 1.00V to negative pin (PD1)
2. Upload the `analogReadEnableDifferential.ino` sketch to your AVR DA board.
3. Open a serial monitor to view the recorded readings.
4. Modify input values for required ranges
 - Signal generator (NEG): Manually set `VAINN` with value.
 - DAC (POS): Manually set `VAINP` with value and modify `Comparator.reference` 
 in `setDAC()` function.
 - VREF: Manually set `VADCREF` with value and modify VREF mode from listed 
options in `setVREF()` function.

## Expected Output
The DAC is routed to act as the POSITIVE pin at 1.024V. The VREF is also set to 
1.024V. The DAC (POS) acts as the expected value or zero point. The VREF acts as 
the magnitude. With the signal generator (NEG pin PD1) set to 1V the output ADC 
value should be 0, corresponding with the DAC (POS) value. Modification of the 
signal generator (NEG) input will have an inverse effect on ADC output. 

## Results
Result sample output demonstrates the output variations in modifying the postive 
and negative input volatges and toggling single ended or differential mode. The
results trends are consistent with expected values.
