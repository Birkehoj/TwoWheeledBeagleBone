#pragma once

#include <cstdint>

namespace BeagleBoneIO::LEDControl
{
enum class LEDType : uint8_t
{
	GREEN,
	RED,
	BAT25,
	BAT50,
	BAT75,
	BAT100,
};

void SetTrigger(char const* filePath, char const* triggerType);
void SetBrightness(char const* filePath, uint8_t brightness);

template <LEDType ledType>
class LED
{
public:
	LED()
	{
		EnableHeartBeat();
	}
	~LED()
	{
		TurnOn(false);
	}

	inline void EnablePeriodicBlick()
	{
		SetTriggerType("timer");
	}

	inline void EnableHeartBeat()
	{
		SetTriggerType("heartbeat");
	}

#define LED_PATH "/sys/devices/platform/leds/leds/"
#define GREEN_TYPE LED_PATH "green/"
#define RED_TYPE LED_PATH "red/"
#define BRIGHTNESS_PATH "brightness"

	inline void TurnOn(bool on, uint8_t brightness=10)
	{
		if(!on)
			brightness = 0;

		SetTriggerType("none");

		if constexpr(ledType == LEDType::GREEN)
		{
			SetBrightness(GREEN_TYPE BRIGHTNESS_PATH, brightness);
		}
		else if(ledType == LEDType::RED)
		{
			SetBrightness(RED_TYPE BRIGHTNESS_PATH, brightness);
		}
		// possible other types one could support
//		switch (type_)
//		{
//		case LEDType::GREEN:
//			return "green";
//		case LEDType::RED:
//			return "red";
//		case LEDType::BAT25:
//			return "bat25";
//		case LEDType::BAT50:
//			return "bat50";
//		case LEDType::BAT75:
//			return "bat75";
//		case LEDType::BAT100:
//			return "bat100";
//		}
	}
private:
#define TRIGGER_PATH "trigger"
	inline void SetTriggerType(char const* triggerType)
	{
		if constexpr(ledType == LEDType::GREEN)
		{
			SetTrigger(GREEN_TYPE TRIGGER_PATH, triggerType);
		}
		else if(ledType == LEDType::RED)
		{
			SetTrigger(RED_TYPE TRIGGER_PATH, triggerType);
		}
	}
#undef TRIGGER_PATH
#undef BRIGHTNESS_PATH
#undef GREEN_TYPE
#undef RED_TYPE
#undef LED_PATH
};



}
