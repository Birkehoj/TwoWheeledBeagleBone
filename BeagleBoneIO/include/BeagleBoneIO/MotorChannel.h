#ifndef BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_MOTORCHANNEL_H_
#define BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_MOTORCHANNEL_H_

namespace BeagleBoneIO {
enum class ChannelNumber {
  all,
  one,
  two,
  three,
  four,
};

class MotorChannel {
 public:
  explicit MotorChannel(int pwmFrequency = 25000);
  ~MotorChannel();
  MotorChannel(const MotorChannel& other) = delete;
  MotorChannel& operator=(const MotorChannel& other) = delete;
  MotorChannel(MotorChannel&& other) = default;
  MotorChannel& operator=(MotorChannel&& other) = default;
  // cppcheck-suppress functionStatic
  void Set(ChannelNumber ch, double duty);  // cppcheck-suppress
  // cppcheck-suppress functionStatic
  void BreakMotor(ChannelNumber ch);
  // cppcheck-suppress functionStatic
  void EnableFreeSpin(ChannelNumber ch);
};
}  // namespace BeagleBoneIO

#endif  // BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_MOTORCHANNEL_H_
