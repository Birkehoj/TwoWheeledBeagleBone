#ifndef BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_LEDCONTROL_H_
#define BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_LEDCONTROL_H_

#include <bits/stdint-uintn.h>  // cstdint but iwyu needs this
#include <cstdint>

namespace BeagleBoneIO
{
namespace Details
{
void setTrigger(char const *filePath, char const *triggerType);
void setBrightness(char const *filePath, uint8_t brightness);
}  // namespace Details

enum class LEDType : uint8_t
{
	GREEN,
	RED,
	//  BAT25,
	//  BAT50,
	//  BAT75,
	//  BAT100,
};

template <LEDType ledType>
class LED
{
public:
	LED() noexcept
	{
		enableHeartBeat();
	}
	~LED() noexcept
	{
		turnOff();
	}
	LED(const LED &) = default;
	LED &operator=(const LED &) = default;
	LED(LED &&) noexcept = default;
	LED &operator=(LED &&) noexcept = default;

	inline void enablePeriodicBlick() noexcept
	{
		setTriggerType("timer");
	}

	inline void enableHeartBeat() noexcept
	{
		setTriggerType("heartbeat");
	}

#define LED_PATH "/sys/devices/platform/leds/leds/"  // NOLINT
#define GREEN_TYPE LED_PATH "green/"				 // NOLINT
#define RED_TYPE LED_PATH "red/"					 // NOLINT
#define BRIGHTNESS_PATH "brightness"				 // NOLINT

	inline void turnOff() noexcept
	{
		turnOn(0);
	}

	static constexpr auto defaultBrightness{UINT8_C(10)};
	inline void turnOn(uint8_t brightness = defaultBrightness) noexcept
	{
		setTriggerType("none");

		if constexpr (ledType == LEDType::GREEN)
		{
			Details::setBrightness(GREEN_TYPE BRIGHTNESS_PATH, brightness);
		}
		else if (ledType == LEDType::RED)
		{
			Details::setBrightness(RED_TYPE BRIGHTNESS_PATH, brightness);
		}
		// possible other types one could support
		// switch (type_)
		// {
		// case LEDType::GREEN:
		// return "green";
		// case LEDType::RED:
		// return "red";
		// case LEDType::BAT25:
		// return "bat25";
		// case LEDType::BAT50:
		// return "bat50";
		// case LEDType::BAT75:
		// return "bat75";
		// case LEDType::BAT100:
		// return "bat100";
		// }
	}

private:
#define TRIGGER_PATH "trigger"  // NOLINT
	// cppcheck-suppress functionStatic; not static to maintain invarinances
	inline void setTriggerType(char const *triggerType) noexcept
	{
		if constexpr (ledType == LEDType::GREEN)
		{
			Details::setTrigger(GREEN_TYPE TRIGGER_PATH, triggerType);
		}
		else if (ledType == LEDType::RED)
		{
			Details::setTrigger(RED_TYPE TRIGGER_PATH, triggerType);
		}
	}
#undef TRIGGER_PATH
#undef BRIGHTNESS_PATH
#undef GREEN_TYPE
#undef RED_TYPE
#undef LED_PATH
};
}  // namespace BeagleBoneIO

#endif  // BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_LEDCONTROL_H_
