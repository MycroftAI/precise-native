MFCC
====

MFCC extractor class for use with real-time audio callbacks.


This code has been adapted from libmfcc (https://code.google.com/p/libmfcc/) 
to work in the context of a real-time audio callback in C++.
MFCC specific calculations are done at initialization to minimize calculations
in the callback. Although it works, there is more that can be done to streamline 
this further.

Example call:
```c++

int sr = 44100; // Sample rate
int FFTlen = 512; // Length of FFT window
int specLen = FFTlen/2+1; // length of resulting magnitude spectrum
int numFilters = 48; // number of filters for MFCC calc
int numCoeffs = 20; // number of MFCC coefficients to calculate

// Allocate space for spectrum and MFCCs
float *spectrum = new float[specLen];
float *mfccs = new float[numCoeffs];

// TODO:
// calculate magnitude-spectrum of a frame of audio
// using FFTW or similar

// Create and init MFCC class
MFCC mfcc;
mfcc.init(sr, numFilters, specLen, numCoeffs);
// Extract MFCCs
mfcc.getCoefficients(spectrum, mfccs);

```
