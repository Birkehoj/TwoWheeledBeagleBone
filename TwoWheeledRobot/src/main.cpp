#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "BeagleBoneIO/EncoderEqep.h"
#include "BeagleBoneIO/LEDControl.h"
#include "BeagleBoneIO/MotorChannel.h"

namespace Ch = std::chrono;
constexpr auto leftMotorNo = BeagleBoneIO::ChannelNumber::four;

static volatile std::atomic_bool continueRunning = true;

static void my_function(int /*sig*/) { continueRunning = false; }

int main() {
  // Register signals
  signal(SIGINT, my_function);
  BeagleBoneIO::EncoderEqep leftEncoder{BeagleBoneIO::EncoderPosition::first};
  BeagleBoneIO::MotorChannel leftMotor;  // 4, right = 1
  std::cout << "Two wheeled robot operational" << std::endl;
  std::cout << "Testing LED's" << std::endl;
  using BeagleBoneIO::LED;
  using BeagleBoneIO::LEDType;
  LED<LEDType::GREEN> greenLED;
  LED<LEDType::RED> redLED;
  redLED.EnablePeriodicBlick();
  greenLED.TurnOn(true, UINT8_MAX);
  unsigned count = 0;
  bool lightInLed = false;
  Ch::time_point now = Ch::steady_clock::now();
  leftMotor.Set(leftMotorNo, 0.2);
  //  leftEncoder.Write(0);
  while (continueRunning) {
    using namespace std::chrono_literals;  // NOLINT(build/namespaces)
    Ch::time_point nextAwakeTime = Ch::steady_clock::now() + 10ms;
    if (++count > 100) {
      lightInLed = !lightInLed;
      greenLED.TurnOn(lightInLed, 100);
      count = 0;
      // auto duration =
      // Ch::duration_cast<Ch::milliseconds>(Ch::steady_clock::now() - now);
      now = Ch::steady_clock::now();
      // std::cout << "Time elabsed " << duration.count()
      //<< std::endl;
      std::cout << leftEncoder.Read() << "\n";
    }
    std::this_thread::sleep_until(nextAwakeTime);
  }
  leftMotor.EnableFreeSpin(leftMotorNo);
  std::cout << "Shutting down" << std::endl;
  return EXIT_SUCCESS;
}
