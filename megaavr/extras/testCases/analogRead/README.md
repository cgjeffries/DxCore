# ADC analogRead 
This test case demonstrates the verified output of analogRead function.

ADC caculation for `analogRead` function provided in the data sheet is as follows;
 - Single-ended 10-bit conversion: ( `V_AINP` / `V_ADCREF` ) * 1024; 
 - Single-ended 12-bit conversion: ( `V_AINP` / `V_ADCREF` ) * 4096; 
 - Differential 10-bit conversion: ( (`V_AINP` - `V_AINN`) / `V_ADCREF` ) * 512;
 - Differential 12-bit conversion:  ( (`V_AINP` - `V_AINN`) / `V_ADCREF` ) * 2048; 
 

For single ended `V_AINP` is the `EXTERNAL` pin `PD0`. However, for differential 
the DAC only routes to the `MUXPOS` register (`V_AINP`), meaning the `EXTERNAL` 
pin switches to negative (`V_AINN`) giving us the following equations;
 - Single-ended 10-bit conversion: ( `EXTERNAL_PIN` / `V_ADCREF` ) * 1024; 
 - Single-ended 12-bit conversion: ( `EXTERNAL_PIN` / `V_ADCREF` ) * 4096; 
 - Differential 10-bit conversion: ( (`DAC_REF` - `EXTERNAL_PIN`) / `V_ADCREF` ) * 512;
 - Differential 12-bit conversion:  ( (`DAC_REF` - `EXTERNAL_PIN`) / `V_ADCREF` ) * 2048;
 
## Instructions
1. Connect AVR128DA48 board to the signal noise generator so it is providing input
to PD0 of the DA board.
2. Upload the sketch to the DA board.
3. View results in your favorite serial terminal (We used TeraTerm)
4. Default test has `V_ADCREF` set to 1.024 and `DAC_REF` at 2.048. Modify `EXTERNAL_PIN`
volatge (DC value of signal noise generator) to desired test value.
    - Single-ended: Signal Noise generator should be set to DC between 0 and 1.0 V 
    for valid readings.
    - Differential: Signal Noise generator should be set from 1.0 V to 3.0 V (max 
 possible output was 2.5 V for our generator) for valid output.
5. Upload sketch and review Expected vs Result output.

## Results
Single-ended results are within expect values. With `V_ADCREF` set to 1.024V and 
`DAC_REF` at 2.048V the `analogRead` function produced average outputs of ~900 
where expectd value was 749.  Expected input for `EXTERNAL` was set to 0.75V. When 
the signal noise generator is reduced to 0.6V the expected matches the result 
almost perfectly. 

Differential results do not match predicted values. With any given setting the 
ADC is returning a value as if the DAC is divided in half. I am unable to explain 
or rationalize this behavior. The modified behavior is shown in the equations 
provided.
 - Differential 10-bit conversion: ( (`DAC_REF` - (`EXTERNAL_PIN` / 2)) / `V_ADCREF` ) * 512;
 - Differential 12-bit conversion:  ( (`DAC_REF` - (`EXTERNAL_PIN` / 2)) / `V_ADCREF` ) * 2048;
