#include<cstdlib>
#include <iostream>
#include <atomic>
#include "BeagleBoneIO/LEDControl.h"

#include <signal.h> //  our new library
volatile std::atomic_bool continueRunning = true;
static void my_function(int /*sig*/){ // can be called asynchronously
  continueRunning = false; // set flag
}

int main()
{
    // Register signals
    signal(SIGINT, my_function);
    std::cout << "Two wheeled robot operational" << std::endl;
    std::cout << "Testing LED's" << std::endl;
    BeagleBoneIO::LEDControl::LED greenLED(BeagleBoneIO::LEDControl::LEDType::GREEN);
    BeagleBoneIO::LEDControl::LED redLED(BeagleBoneIO::LEDControl::LEDType::RED);
    greenLED.EnablePeriodicBlick();
    while(continueRunning)
    {
    }
    return EXIT_SUCCESS;
}
