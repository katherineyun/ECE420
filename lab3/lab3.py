import numpy as np
import matplotlib.pyplot as plt
from scipy.io.wavfile import read, write
from numpy.fft import fft, ifft
from scipy import signal

FRAME_SIZE = 1024
ZP_FACTOR = 2
FFT_SIZE = FRAME_SIZE * ZP_FACTOR

################## YOUR CODE HERE ######################
def ece420ProcessFrame(frame):
    curFft = np.zeros(FFT_SIZE)
    window = signal.hamming(FRAME_SIZE)
    signal_win = window*frame               #apply windowing
    curFft = fft(signal_win, n = FFT_SIZE)         #zero pad the rest to FFT_Size
    curFfreq = curFft[0:FRAME_SIZE]
    output = np.log(np.square(np.abs(curFfreq))) / 20  #convert to power and scale to log

    return output


################# GIVEN CODE BELOW #####################

Fs, data = read('test_vector.wav')

numFrames = int(len(data) / FRAME_SIZE)
bmp = np.zeros((numFrames, FRAME_SIZE))

for i in range(numFrames):
    frame = data[i * FRAME_SIZE : (i + 1) * FRAME_SIZE]
    curFft = ece420ProcessFrame(frame)
    bmp[i, :] = curFft   #bmp is same as frame_size

plt.figure()
plt.pcolormesh(bmp.T, vmin=0, vmax=1)
plt.axis('tight')
plt.show()