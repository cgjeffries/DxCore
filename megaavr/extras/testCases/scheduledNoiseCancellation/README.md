# Periodic Noise with scheduled cancellation Test Case
This test case demonstrates the attempt to schedule the increase in sample numbering to correspond with the timing 
of the periodic noise.

## Findings
I have found that the ADC sampling frequency is not fast enough to be able to consistently schedule noise cancellation 
with any frequency of noise higher than 1kHz. Since we are not able to recreate any noise below 45 kHz with the noise 
generator, I am not able to test the functionality but the ino sketch gives an idea as to how it would work with less 
frequent noise.