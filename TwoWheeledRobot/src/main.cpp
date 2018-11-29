#include<cstdlib>
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <csignal>
#include "BeagleBoneIO/LEDControl.h"

namespace Ch = std::chrono;

static volatile std::atomic_bool continueRunning = true;

static void my_function(int /*sig*/) // NOLINT(readability/casting)
{
	continueRunning = false; // set flag
}

int main()
{
	// Register signals
	signal(SIGINT, my_function);
	std::cout << "Two wheeled robot operational" << std::endl;
	std::cout << "Testing LED's" << std::endl;
	using BeagleBoneIO::LEDType;
	using BeagleBoneIO::LED;
	LED<LEDType::GREEN> greenLED;
	LED<LEDType::RED> redLED;
	redLED.EnablePeriodicBlick();
	greenLED.TurnOn(true, UINT8_MAX);
	unsigned count = 0;
	bool lightInLed = false;
	Ch::time_point now = Ch::steady_clock::now();
	while(continueRunning)
	{
		using namespace std::chrono_literals; // NOLINT(build/namespaces)
		Ch::time_point nextAwakeTime = Ch::steady_clock::now() + 10ms;
		if(++count > 100)
		{
			lightInLed = !lightInLed;
			greenLED.TurnOn(lightInLed, 100);
			count = 0;
			auto duration = Ch::duration_cast<Ch::milliseconds>(Ch::steady_clock::now() - now);
			now = Ch::steady_clock::now();
			std::cout << "Time elabsed " << duration.count() << std::endl;
		}
		std::this_thread::sleep_until(nextAwakeTime);
	}
	std::cout << "Shutting down" << std::endl;
	return EXIT_SUCCESS;
}
