#include "BeagleBoneIO/LEDControl.h"
#include<fstream>
#include <iostream>

namespace BeagleBoneIO::LEDControl
{

void SetTrigger(char const* filePath, char const* triggerType)
{
	if(std::ofstream fs(filePath); fs.good())
		fs << triggerType;
}

void SetBrightness(char const* filePath, uint8_t brightness)
{
	if(std::ofstream fs(filePath); fs.good())
	{
		fs << static_cast<int>(brightness);
	}
}
}













