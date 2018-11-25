#include "BeagleBoneIO/LEDControl.h"

#include<fstream>
#include<string>
#include <string_view>
#include <cmath>
#include <cassert>

using namespace BeagleBoneIO::LEDControl;

static constexpr char ledDir[] = "/sys/devices/platform/leds/leds";
static constexpr char triggerFile[] = "trigger";
static constexpr char brightnessFile[] = "brightness";

namespace TriggerType
{
static constexpr char none[] = "none";
static constexpr char timer[] = "timer";
static constexpr char heartbeat[] = "heartbeat";
}

LED::LED(LEDType type)
	: type_{type}
{
	SetTricker(TriggerType::heartbeat);
}

LED::~LED()
{
	TurnOn(false);
}

void LED::EnableHeartBeat()
{
	SetTricker(TriggerType::heartbeat);
}

void LED::EnablePeriodicBlick()
{
	SetTricker(TriggerType::timer);
}

void LED::TurnOn(bool on, uint8_t brightness)
{
	SetTricker(TriggerType::none);
	if(std::ofstream fs(std::string(ledDir) + "/" + LedTypePath() + "/" + brightnessFile); fs.good())
		fs << (on ? brightness : 0);
}

char const* LED::LedTypePath()
{
	switch (type_)
	{
	case LEDType::GREEN:
		return "green";
	case LEDType::RED:
		return "red";
	case LEDType::BAT25:
		return "bat25";
	case LEDType::BAT50:
		return "bat50";
	case LEDType::BAT75:
		return "bat75";
	case LEDType::BAT100:
		return "bat100";
	}
	return "";
}

void LED::SetTricker(char const * const triggerType)
{
	if(std::ofstream fs(std::string(ledDir) + "/" + LedTypePath() + "/" + triggerFile); fs.good())
		fs << triggerType;
}
