import numpy as np
import matplotlib.pyplot as plt
import os

def peak_detection(t, sig, thresh):
    peaks = []
    max_val = -np.Inf
    N = len(sig)
    enter_peak = 0
    for i in range(0, N-2):
        if sig[i] > thresh:
            if sig[i] > max_val:
                max_val = sig[i]
                position = t[i]
            enter_peak = 1
        elif (enter_peak and sig[i-1] < sig[i]):
            peaks.append((position, max_val))
            max_val = -np.Inf
            enter_peak = 0
    return np.array(peaks)
os.chdir('/Users/Katherine/Desktop/ECE420/Lab1')

csv_filename = 'sample_sensor_data.csv'
data = np.genfromtxt(csv_filename, delimiter=',').T
timestamps = (data[0] - data[0, 0])/1000

accel_data = data[1:4]
gyro_data = data[4:-1]

max_peaks = peak_detection(timestamps, accel_data[0], 3)
plt.plot(timestamps, accel_data[0])
plt.scatter(max_peaks[:, 0], max_peaks[:, 1], color = 'red')
plt.xlabel('Time')
plt.ylabel('Meters per second')
plt.title('First axis of accelerometer data')
plt.show()
