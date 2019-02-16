#include "BeagleBoneIO/MotorChannel.h"
#include <stdexcept>
#include <utility>
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
void MotorChannel::set(ChannelNumber ch, double duty) {
  callErrorCodeToException(&rc_motor_set, static_cast<int>(ch), duty);
}

// cppcheck-suppress unusedFunction
void MotorChannel::breakMotor(ChannelNumber ch) {
  callErrorCodeToException(&rc_motor_brake, static_cast<int>(ch));
}

// cppcheck-suppress unusedFunction
void MotorChannel::enableFreeSpin(ChannelNumber ch) {
  callErrorCodeToException(&rc_motor_free_spin, static_cast<int>(ch));
}

}  // namespace BeagleBoneIO
