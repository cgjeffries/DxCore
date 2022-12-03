# ADC Sample Delay Test Case
This test case demonstrates changing the delay before taking each ADC sample by
cycling between several different sample delay settings and outputting the results
of taking 64 samples at each setting over serial. 

## Instructions
1. Upload the `analogReadSampleDelay.ino` sketch to your AVRDA board.
2. Open a serial monitor to view the recorded readings.

## Expected Output
When changing the sample delay on its own with no noise added to the analog signal
and accumulation disabled, no significant change in ADC readings is expected.

## Results
Example results are recorded in `results.log` and analyzed in `results.xlsx`. These
results show that changing the sample delay is functioning as expected. 
