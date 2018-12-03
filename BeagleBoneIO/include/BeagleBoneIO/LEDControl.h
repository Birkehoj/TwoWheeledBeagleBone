#ifndef BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_LEDCONTROL_H_
#define BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_LEDCONTROL_H_

#include <cstdint>

namespace BeagleBoneIO {
namespace Details {
void SetTrigger(char const* filePath, char const* triggerType) noexcept;
void SetBrightness(char const* filePath, uint8_t brightness) noexcept;
}  // namespace Details

enum class LEDType : uint8_t {
  GREEN,
  RED,
  BAT25,
  BAT50,
  BAT75,
  BAT100,
};

template <LEDType ledType>
class LED {
 public:
  LED() noexcept { EnableHeartBeat(); }
  ~LED() noexcept { TurnOn(false); }

  inline void EnablePeriodicBlick() noexcept { SetTriggerType("timer"); }

  inline void EnableHeartBeat() noexcept { SetTriggerType("heartbeat"); }

#define LED_PATH "/sys/devices/platform/leds/leds/"
#define GREEN_TYPE LED_PATH "green/"
#define RED_TYPE LED_PATH "red/"
#define BRIGHTNESS_PATH "brightness"

  inline void TurnOn(bool on, uint8_t brightness = 10) noexcept {
    if (!on) {
      brightness = 0;
    }

    SetTriggerType("none");

    if constexpr (ledType == LEDType::GREEN) {
      Details::SetBrightness(GREEN_TYPE BRIGHTNESS_PATH, brightness);
    } else if (ledType == LEDType::RED) {
      Details::SetBrightness(RED_TYPE BRIGHTNESS_PATH, brightness);
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
#define TRIGGER_PATH "trigger"
  inline void SetTriggerType(char const* triggerType) noexcept {
    if constexpr (ledType == LEDType::GREEN) {
      Details::SetTrigger(GREEN_TYPE TRIGGER_PATH, triggerType);
    } else if (ledType == LEDType::RED) {
      Details::SetTrigger(RED_TYPE TRIGGER_PATH, triggerType);
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
