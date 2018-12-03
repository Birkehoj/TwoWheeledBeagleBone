#include "BeagleBoneIO/MotorChannel.h"
#include <stdexcept>
// cppcheck-suppress missingInclude
#include "rc/motor.h"

template <typename CFunction, typename... Args>
static inline void callErrorCodeToException(CFunction function,
                                            Args&&... args) {
  if (function(std::forward<Args>(args)...) != 0) {
    throw std::runtime_error(
        "Failed to operate motors. Look for reasons in log.");
  }
}

namespace BeagleBoneIO {
MotorChannel::MotorChannel(int pwmFrequency) {
  callErrorCodeToException(&rc_motor_init_freq, pwmFrequency);
}

MotorChannel::~MotorChannel() { callErrorCodeToException(&rc_motor_cleanup); }

// cppcheck-suppress unusedFunction
void MotorChannel::Set(ChannelNumber ch, double duty) {
  callErrorCodeToException(&rc_motor_set, static_cast<int>(ch), duty);
}

// cppcheck-suppress unusedFunction
void MotorChannel::BreakMotor(ChannelNumber ch) {
  callErrorCodeToException(&rc_motor_brake, static_cast<int>(ch));
}

// cppcheck-suppress unusedFunction
void MotorChannel::EnableFreeSpin(ChannelNumber ch) {
  callErrorCodeToException(&rc_motor_free_spin, static_cast<int>(ch));
}

}  // namespace BeagleBoneIO
