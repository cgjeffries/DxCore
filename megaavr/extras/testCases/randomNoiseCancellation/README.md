# Random Noise Cancellation Demo
This test sketch dmonstrates performing noise cancellation on a signal with
random noise added by using sample accumulation.

## Instructions
1. Connect the signal generator board to your Curiosity Nano, with the signal output
connected to A0 (PD0)
2. Configure the signal generator to output 1.25v constant DC voltage
3. Configure the signal generator to output the desired level of random noise
4. Upload the `randomNoiseCancellation.ino` sketch to your AVRDA board.
5. Open a serial monitor to view the recorded readings.
