//
// Created by daran on 1/12/2017 to be used in ECE420 Sp17 for the first time.
// Modified by dwang49 on 1/1/2018 to adapt to Android 7.0 and Shield Tablet updates.
//

#include "ece420_main.h"

// Student Variables
#define FRAME_SIZE 128

// FIR Filter Function Defined here located at the bottom
int16_t firFilter(int16_t sample);

void ece420ProcessFrame(sample_buf *dataBuf) {
    // Keep in mind, we only have a small amount of time to process each buffer!
    struct timeval start;
    gettimeofday(&start, NULL);

    // Using {} initializes all values in the array to zero
    int16_t bufferIn[FRAME_SIZE] = {};
    int16_t bufferOut[FRAME_SIZE] = {};

    // Your buffer conversion (unpacking) here
    // Fetch data sample from dataBuf->buf_[], unpack and put into bufferIn[]
    // ******************** START YOUR CODE HERE ******************** //

    for(int sampleIdx = 0; sampleIdx < FRAME_SIZE; sampleIdx++)
    {
        uint16_t firstB = dataBuf->buf_[2*sampleIdx+1];
        uint16_t secondB = dataBuf->buf_[2*sampleIdx];

        int16_t sample = (firstB << 8) + secondB;

        bufferIn[sampleIdx] = sample;
    }


    // ********************* END YOUR CODE HERE ********************* //

    // Loop code provided as a suggestion. This loop simulates sample-by-sample processing.
    for (int sampleIdx = 0; sampleIdx < FRAME_SIZE; sampleIdx++) {
        // Grab one sample from bufferIn[]
        int16_t sample = bufferIn[sampleIdx];
        // Call your filFilter function
       int16_t output = firFilter(sample);
        // Grab result and put into bufferOut[]
        bufferOut[sampleIdx] = output;
    }

    // Your buffer conversion (packing) here
    // Fetch data sample from bufferOut[], pack them and put back into dataBuf->buf_[]
    // ******************** START YOUR CODE HERE ******************** //
    for (int sampleIdx = 0; sampleIdx < FRAME_SIZE; sampleIdx++)
    {
        uint8_t second = bufferOut[sampleIdx];
        uint16_t temp = bufferOut[sampleIdx] - second;
        uint8_t first = temp >> 8;

        dataBuf->buf_[2*sampleIdx] = second;
        dataBuf->buf_[2*sampleIdx+1] = first;

    }


    // ********************* END YOUR CODE HERE ********************* //

	// Log the processing time to Android Monitor or Logcat window at the bottom
    struct timeval end;
    gettimeofday(&end, NULL);
    LOGD("Loop timer: %ld us",  ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

}

// TODO: Change N_TAPS to match your filter design
#define N_TAPS 131
// TODO: Change myfilter to contain the coefficients of your designed filter.
double myfilter[N_TAPS] = {2.70155304e-04,6.14829305e-04,9.63884117e-04,1.27190289e-03
        ,1.49032695e-03,1.57190379e-03,1.47550873e-03,1.17090106e-03
        ,6.42941076e-04,-1.05196071e-04,-1.05021790e-03,-2.14863102e-03
        ,-3.33854525e-03,-4.54336753e-03,-5.67720740e-03,-6.65163788e-03
        ,-7.38329750e-03,-7.80169704e-03,-7.85652319e-03,-7.52372041e-03
        ,-6.80968775e-03,-5.75304864e-03,-4.42363207e-03,-2.91853048e-03
        ,-1.35535595e-03,1.36920181e-04,1.42891134e-03,2.40270167e-03
        ,2.96368467e-03,3.05129501e-03,2.64759314e-03,1.78277426e-03
        ,5.36874313e-04,-9.62777021e-04,-2.54847119e-03,-4.02315243e-03
        ,-5.17494711e-03,-5.79423335e-03,-5.69201589e-03,-4.71818017e-03
        ,-2.77811694e-03,1.53753830e-04,4.02486990e-03,8.70085777e-03
        ,1.39679652e-02,1.95418046e-02,2.50821292e-02,3.02128771e-02
        ,3.45462660e-02,3.77093520e-02,3.93711973e-02,3.92686648e-02
        ,3.72288745e-02,3.31865293e-02,2.71946328e-02,1.94275597e-02
        ,1.01759714e-02,-1.66347231e-04,-1.11230594e-02,-2.21620299e-02
        ,-3.27265554e-02,-4.22690087e-02,-5.02846220e-02,-5.63430895e-02
        ,-6.01157934e-02,9.38603251e-01,-6.01157934e-02,-5.63430895e-02
        ,-5.02846220e-02,-4.22690087e-02,-3.27265554e-02,-2.21620299e-02
        ,-1.11230594e-02,-1.66347231e-04,1.01759714e-02,1.94275597e-02
        ,2.71946328e-02,3.31865293e-02,3.72288745e-02,3.92686648e-02
        ,3.93711973e-02,3.77093520e-02,3.45462660e-02,3.02128771e-02
        ,2.50821292e-02,1.95418046e-02,1.39679652e-02,8.70085777e-03
        ,4.02486990e-03,1.53753830e-04,-2.77811694e-03,-4.71818017e-03
        ,-5.69201589e-03,-5.79423335e-03,-5.17494711e-03,-4.02315243e-03
        ,-2.54847119e-03,-9.62777021e-04,5.36874313e-04,1.78277426e-03
        ,2.64759314e-03,3.05129501e-03,2.96368467e-03,2.40270167e-03
        ,1.42891134e-03,1.36920181e-04,-1.35535595e-03,-2.91853048e-03
        ,-4.42363207e-03,-5.75304864e-03,-6.80968775e-03,-7.52372041e-03
        ,-7.85652319e-03,-7.80169704e-03,-7.38329750e-03,-6.65163788e-03
        ,-5.67720740e-03,-4.54336753e-03,-3.33854525e-03,-2.14863102e-03
        ,-1.05021790e-03,-1.05196071e-04,6.42941076e-04,1.17090106e-03
        ,1.47550873e-03,1.57190379e-03,1.49032695e-03,1.27190289e-03
        ,9.63884117e-04,6.14829305e-04,2.70155304e-04};

// Circular Buffer
int16_t circBuf[N_TAPS] = {};
int16_t circBufIdx = 0;
int flag = 0;
// FirFilter Function
int16_t firFilter(int16_t sample) {
    // This function simulates sample-by-sample processing. Here you will
    // implement an FIR filter such as:
    //
    // y[n] = a x[n] + b x[n-1] + c x[n-2] + ...
    //
    // You will maintain a circular buffer to store your prior samples
    // x[n-1], x[n-2], ..., x[n-k]. Suggested initializations circBuf
    // and circBufIdx are given.
    //
    // Input 'sample' is the current sample x[n].
    // ******************** START YOUR CODE HERE ******************** //
    int16_t output = 0;
    circBuf[circBufIdx%N_TAPS] = sample;

    circBufIdx = (circBufIdx +1) % N_TAPS;

    if (flag==0 && circBufIdx== (N_TAPS - 1)){
        flag = 1;
    }

    if (flag == 0)
    {
        for (unsigned i=0; i<circBufIdx; i++)
            output += circBuf[circBufIdx -i ] * myfilter[i];
    }

    else
    {
        for (unsigned i=0; i<N_TAPS; i++)
            output += circBuf[(N_TAPS + circBufIdx -i)%N_TAPS] * myfilter[i];
    }


    // ********************* END YOUR CODE HERE ********************* //
    return output;
}
