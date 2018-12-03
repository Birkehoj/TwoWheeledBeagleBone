#ifndef BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_ENCODEREQEP_H_
#define BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_ENCODEREQEP_H_
#include <fstream>
namespace BeagleBoneIO {
enum class EncoderPosition {
  first,
  second,
  third,
};

class EncoderEqep {
 public:
  explicit EncoderEqep(EncoderPosition pos);
  // cppcheck-suppress functionConst; ifstream operator>> is not const
  [[nodiscard]] int Read();

 private:
  std::ifstream eqepPosFile;
};
}  // namespace BeagleBoneIO
#endif  // BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_ENCODEREQEP_H_
