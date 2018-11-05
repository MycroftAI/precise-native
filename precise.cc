#include <iostream>
#include <unistd.h>
#include "RealtimeProcessor.hpp"
#include "AudioManager.hpp"


int main(int argc, char *argv[]) {
	RealtimeProcessor processor;
	auto onAudio = [&](float *f, size_t n)
	{
		processor.onAudio(f, n);
        for (auto i : processor.outputFftData) {
            std::cout << std::abs(i) << "\t";
        }
        std::cout << std::endl;
	};

	AudioManager audioManager(onAudio);
	while(true) {
        usleep(100000);
    }
}
