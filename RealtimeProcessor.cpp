/* 
 * Copyright Mycroft AI, Inc. 2017 - All Rights Reserved
 */

#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <iostream>
#include "RealtimeProcessor.hpp"

using namespace std;

RealtimeProcessor::RealtimeProcessor()
        : mfcc(AudioManager::sampleRate, numFilters, fftSize, mfccSize) {}

void RealtimeProcessor::onAudio(float *in, size_t n) {
    if (n != hopLen) {
        std::cerr << "Invalid audio length recieved: " << n << std::endl;
        return;
    }

    // Shift buffer and mfccs back by one
    float tempBuffer[bufferSize - hopLen];
    memcpy(tempBuffer, buffer + hopLen, sizeof(tempBuffer));
    memcpy(buffer, tempBuffer, sizeof(tempBuffer));

    memcpy(buffer + bufferSize - n, in, n * sizeof(in[0]));
    memcpy(mfccs, mfccs + 1, (numMfccs - 1) * sizeof(mfccs[0]));

    memcpy(inputFftData, buffer + bufferSize - fftSize, fftSize * sizeof(buffer[0]));

    kissfft<float> fft(fftSize, false);
    for (auto &i : outputFftData) {
        i = 0.f;
    }
    fft.transform_real(inputFftData, outputFftData);
    for (unsigned int i = 0; i < fftSize; ++i) {
        realFftData[i] = std::abs(outputFftData[i]);
    }

    float mfccData[mfccSize];
    mfcc.getCoefficients(realFftData, mfccData);
    memcpy(mfccs + numMfccs - 1, mfccData, sizeof(mfccData));
}

void RealtimeProcessor::process(const std::vector<float> &audio) {
    for (unsigned int i = AudioManager::chunkSize; i < audio.size(); i += AudioManager::chunkSize) {
        vector<float> chunk(audio.begin() + i - AudioManager::chunkSize, audio.begin() + i);
        onAudio(chunk.data(), chunk.size());
    }
}

