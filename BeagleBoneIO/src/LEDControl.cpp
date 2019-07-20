#include "BeagleBoneIO/LEDControl.h"

#include <fstream>

namespace BeagleBoneIO::Details
{
void setTrigger(char const *filePath, char const *triggerType)
{
	std::ofstream fs(filePath);
	fs.exceptions();
	fs << triggerType;
}

void setBrightness(char const *filePath, uint8_t brightness)
{
	std::ofstream fs(filePath);
	fs.exceptions();
	fs << static_cast<int>(brightness);
}
}  // namespace BeagleBoneIO::Details
