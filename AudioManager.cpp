/* 
 * Copyright Mycroft AI, Inc. 2017 - All Rights Reserved
 */

#include <portaudiocpp/PortAudioCpp.hxx>
#include <iostream>

#include "AudioManager.hpp"


static int processAudio(const void *inputBuffer, void *outputBuffer, unsigned long numFrames,
						const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
						void *userData)
{
	const AudioManager::AudioFunc &onAudio = *reinterpret_cast<AudioManager::AudioFunc*> (userData);
	onAudio((float*) inputBuffer, numFrames);
	return 0;
}

void AudioManager::printDevices() {
	std::cout << "=== Devices ===" << std::endl;
	
	for (portaudio::System::DeviceIterator it = sys.devicesBegin(); it != sys.devicesEnd(); ++it) {
		std::cout << " - Name: " << it->name() << ", Index: " << it->index() << std::endl;
	}
}

AudioManager::AudioManager(const AudioFunc &onAudio)
: autoSystem(), sys(portaudio::System::instance()), inputDev(sys.defaultInputDevice()), outputDev(sys.defaultOutputDevice()),
	inputParameters(inputDev, numChanIn, portaudio::FLOAT32, true, inputDev.defaultLowInputLatency(), nullptr),
	outputParameters(outputDev, numChanOut, portaudio::FLOAT32, true, outputDev.defaultLowOutputLatency(), nullptr),
	streamParams(inputParameters, outputParameters, sampleRate, chunkSize, paNoFlag),
	stream(streamParams, processAudio, (void*) & onAudio)
{
	stream.start();
}

bool AudioManager::isStreamOpen()
{
	return stream.isOpen();
}

AudioManager::~AudioManager()
{
	stream.close();
}
