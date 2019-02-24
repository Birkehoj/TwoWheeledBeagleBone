#include "BeagleBoneIO/LEDControl.h"

#include <fstream>

namespace BeagleBoneIO
{
namespace Details
{
void SetTrigger(char const *filePath, char const *triggerType) noexcept
{
	std::ofstream fs(filePath);
	fs.exceptions();
	fs << triggerType;
}

void SetBrightness(char const *filePath, uint8_t brightness) noexcept
{
	std::ofstream fs(filePath);
	fs.exceptions();
	fs << static_cast<int>(brightness);
}
}  // namespace Details
}  // namespace BeagleBoneIO
