import numpy as np
from numpy.fft import fft
import matplotlib.pyplot as plt
import scipy.io.wavfile as spwav
#from mpldatacursor import datacursor
import sys

plt.style.use('ggplot')

# Note: this epoch list only holds for "test_vector_all_voiced.wav"
epoch_marks_orig = np.load("test_vector_all_voiced_epochs.npy")
F_s, audio_data = spwav.read("test_vector_all_voiced.wav")
N = len(audio_data)

######################## YOUR CODE HERE ##############################

F_new = 420
new_epoch_spacing = int(F_s/F_new)  #P1
audio_out = np.zeros(N)

# Suggested loop
for i in range(0, N, new_epoch_spacing):
    e = np.argmin(abs(epoch_marks_orig - i))
    cloest_e = epoch_marks_orig[e]

    if (e==0):
        before = epoch_marks_orig[0]
        after = epoch_marks_orig[1]
        P_0  = cloest_e
    elif(e == len(epoch_marks_orig)-1):
        before = epoch_marks_orig[e - 1]
        after = epoch_marks_orig[e]
        P_0 = int((after - before) / 2)
    else:
        before = epoch_marks_orig[e-1]
        after = epoch_marks_orig[e+1]
        P_0 = int((after - before) / 2)
    data = audio_data[(cloest_e - P_0):(cloest_e + P_0+1)]
    window = np.hanning(2 * P_0 + 1)
    windowed_response = window * data
    print(P_0*2)
    if(e==0):
        audio_out[0:2*P_0+1] += windowed_response
    elif(e == len(epoch_marks_orig)-1):
        audio_out[N-2*P_0-2:N-1] += windowed_response
    else:
        audio_out[i-P_0:(i + P_0 + 1)] += windowed_response

spwav.write("audio_out.wav", rate=F_s, data=audio_out)
plt.plot(audio_data, 'g')
plt.show()
plt.plot(audio_out, 'b')
plt.show()



    # https://courses.engr.illinois.edu/ece420/lab5/lab/#overlap-add-algorithm
    # Your OLA code here




