#include "BeagleBoneIO/LEDControl.h"
#include <fstream>
#include <iostream>

namespace BeagleBoneIO {
namespace Details {
void SetTrigger(char const* filePath, char const* triggerType) noexcept {
  // cppcheck-suppress syntaxError; lack of c++17 support in 1.85
  if (std::ofstream fs(filePath); fs.good()) {
    fs << triggerType;
  }
}

void SetBrightness(char const* filePath, uint8_t brightness) noexcept {
  if (std::ofstream fs(filePath); fs.good()) {
    fs << static_cast<int>(brightness);
  }
}
}  // namespace Details
}  // namespace BeagleBoneIO
