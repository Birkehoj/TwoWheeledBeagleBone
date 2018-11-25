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

class LED
{
public:
	LED(LEDType type);
	~LED();

	void EnableHeartBeat();
	void EnablePeriodicBlick();
	void TurnOn(bool on, uint8_t brightness=10);
private:
	char const* LedTypePath();
	void SetTricker(char const * const triggerType);
	LEDType type_;
};

}
