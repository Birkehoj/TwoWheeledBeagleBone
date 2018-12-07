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
  [[nodiscard]] uint32_t read();

 private:
  std::ifstream m_eqepPosFile;
};
}  // namespace BeagleBoneIO
#endif  // BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_ENCODEREQEP_H_
