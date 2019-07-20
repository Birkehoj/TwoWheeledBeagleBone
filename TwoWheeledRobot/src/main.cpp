
// TODO(Anders Jensen): clang-format why not system headers over own here?
// clang-format off
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "BeagleBoneIO/EncoderEqep.h"
#include "BeagleBoneIO/LEDControl.h"
#include "BeagleBoneIO/MotorsController.h"
// clang-format on

namespace Ch = std::chrono;

constexpr auto leftMotorNo = BeagleBoneIO::ChannelNumber::four;

static volatile std::atomic_bool continueRunning = true;

static void shutdownHandler(int /*sig*/)
{
	std::cout << "shutdown signal detected" << std::endl;
	continueRunning = false;
}

static void term(int /*signum*/)
{
	std::cout << "terminate signal detected" << std::endl;
	continueRunning = false;
}

int main()
{
	// Register signals
	signal(SIGINT, shutdownHandler);
	struct sigaction action
	{
	};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
	action.sa_handler = term;  // NOLINT
#pragma clang diagnostic pop

	sigaction(SIGTERM, &action, nullptr);

	BeagleBoneIO::EncoderEqep leftEncoder{BeagleBoneIO::EncoderPosition::third};
	BeagleBoneIO::MotorsController leftMotor;  // 4, right = 1
	std::cout << "Two wheeled robot operational" << std::endl;
	std::cout << "Testing LED's" << std::endl;
	using BeagleBoneIO::LED;
	using BeagleBoneIO::LEDType;
	LED<LEDType::GREEN> greenLED;
	LED<LEDType::RED> redLED;
	redLED.enablePeriodicBlick();
	greenLED.turnOn(UINT8_MAX);
	unsigned count = 0U;
	bool lightInLed = false;
	constexpr double defaultPower = 0.2;
	leftMotor.set(leftMotorNo, defaultPower);
	//  leftEncoder.Write(0);
	while (continueRunning)
	{
		using namespace std::chrono_literals;  // NOLINT(build/namespaces)
		Ch::time_point nextAwakeTime = Ch::steady_clock::now() + 10ms;
		constexpr unsigned countNoToToggleLed = 100U;
		if (++count > countNoToToggleLed)
		{
			lightInLed = !lightInLed;
			static constexpr auto middleBrightness{UINT8_C(100)};
			greenLED.turnOn(middleBrightness);
			count = 0;
			//      auto duration =
			// Ch::duration_cast<Ch::milliseconds>(Ch::steady_clock::now() -
			//          now);
			//      now = Ch::steady_clock::now();
			// std::cout << "Time elabsed " << duration.count()
			// << std::endl;
			std::cout << "encoder value: " << (leftEncoder.read()) << std::endl;
		}
		std::this_thread::sleep_until(nextAwakeTime);
	}
	leftMotor.enableFreeSpin(leftMotorNo);
	std::cout << "Shutting down" << std::endl;
	return EXIT_SUCCESS;
}
