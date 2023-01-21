# Periodic Noise Cancellation Test Case
This test case demonstrates the changes in output with periodic noise input. This test case 
will test how analogRead output, with a change in number of samples recorded, is affected while 
there is periodic noise in the background

## Instructions
3. Upload the `periodicNoise.ino` sketch to your AVRDA board.
4. Using the noise generator, set the signal source to DC enable, at 1.25V.
5. Enable periodic noise on the noise generator with an amplitude of 0.1 Vpp and a frequency of 96 kHz
6. Open a serial monitor to view the recorded readings.