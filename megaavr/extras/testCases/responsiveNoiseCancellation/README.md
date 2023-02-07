# Responsive Noise Cancellation Test Case
This test case demonstrates the changes in output with a sketch that responds to noise by increasing  
the number of samples being taken to attempt to improve the reading accuracy. When noise is detected 
the next half second of readings assume noise is still present, then the number of readings returns 
back to normal until noise is detected again

## Instructions
1. Upload the `responsiveNoiseCancellation.ino` sketch to your AVRDA board.
2. Using the noise generator, set the signal source to DC enable, at 1.25V.
3. Enable random noise on the noise generator with an amplitude of 0.1 Vpp. 
4. Open a serial monitor to view the recorded readings.