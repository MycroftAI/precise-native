/* 
 * Copyright Mycroft AI, Inc. 2017 - All Rights Reserved
 */

#pragma once

#include <functional>
#include <vector>
#include <portaudiocpp/PortAudioCpp.hxx>

// Class: AudioManager
// Handles Portaudio stream to receive incoming audio
class AudioManager
{
public:
	static const int numChanIn = 1;
	static const int numChanOut = 0;
	static const int sampleRate = 16000;
	static const int chunkSize = 512;

	/* Typedef: AudioFunc
	 * A function that receives audio.
	 * 
	 * Parameters:
	 *     float* - input audio array (1 channel)
	 *     size_t - number of values in array (should be chunkSize)
	 */
	using AudioFunc = std::function<void(float*, size_t)>;

	/* Constructor: AudioManager
	 * Parameters:
	 *     onAudio - function to continuously call to receive audio
	 */
	AudioManager(const AudioFunc &onAudio);
	~AudioManager();
	bool isStreamOpen();
	void printDevices();

private:
	portaudio::AutoSystem autoSystem;
	portaudio::System &sys;
	portaudio::Device &inputDev, &outputDev;
	portaudio::DirectionSpecificStreamParameters inputParameters, outputParameters;
	portaudio::StreamParameters streamParams;
	portaudio::FunCallbackStream stream;
};
