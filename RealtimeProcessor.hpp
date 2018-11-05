/*
 * Copyright Mycroft AI, Inc. 2017 - All Rights Reserved
 */

#pragma once

#include <vector>
#include <memory>
#include <mutex>

#include "mfcc/Mfcc.h"
#include "kissfft/kissfft.hh"
#include "AudioManager.hpp"

// Class: RealtimeProcessor
// Generates speech data realtime from incoming audio
class RealtimeProcessor
{
public:
	static const size_t bufferSize = 2048, fftSize = bufferSize, numFilters = 32,
			mfccSize = 20, hopLen = AudioManager::chunkSize, numHops = fftSize / hopLen,
			numMfccs = bufferSize / hopLen;

	RealtimeProcessor();

	/* Function: onAudio
	 * Audio callback to process data
	 * 
	 * Parameters:
	 *     in - input audio array
	 *     n - number of samples in array
	 */
	void onAudio(float *in, size_t n);
	
	/* Function: process
	 * Run the given audio through the system
	 * 
	 * Parameters:
	 *     wave - raw audio data to read from
	 */
	void process(const std::vector<float> &audio);

	// Variable: fft
	// Fast fourier transform calculator
	float inputFftData[fftSize]{};
	std::complex<float> outputFftData[fftSize]{};
	float realFftData[fftSize];

	// Variable: buffer
	// Audio buffer of past two chunks
	float buffer[bufferSize]{};

	// Variable: mfccs
	// Mel frequency cepstrum coefficients over the past second or so
	float mfccs[numMfccs][mfccSize]{};

private:
	Mfcc mfcc;
};
