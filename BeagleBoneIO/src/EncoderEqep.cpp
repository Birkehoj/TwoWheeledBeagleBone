#include "BeagleBoneIO/EncoderEqep.h"
#include <stdexcept>

using std::string;

#define EQEP_BASE2 "/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep"
#define TO_ENABLED_FILE_PATH(EQ_FILE_PATH) (EQ_FILE_PATH "/enabled")
#define TO_POSITION_FILE_PATH(EQ_FILE_PATH) (EQ_FILE_PATH "/position")

namespace BeagleBoneIO {
EncoderEqep::EncoderEqep(EncoderPosition pos) {
  const string path = [pos] {
    switch (pos) {
      case EncoderPosition::first:
        return "/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep";
      case EncoderPosition::second:
        return "/sys/devices/platform/ocp/48302000.epwmss/48302180.eqep";
      case EncoderPosition::third:
        break;  // fall though instead of return to avoid compiler warning
    }
    return "/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep";
  }();
  const string encoderPosPath = path + "/position";
  if (std::ofstream fs(encoderPosPath); fs.is_open()) {
    fs << 0;
  }
  m_eqepPosFile.open(encoderPosPath);
  std::fstream enabledFs(path + "/enabled");
  if (!m_eqepPosFile.is_open() || !enabledFs.is_open()) {
    throw std::runtime_error("Failed to open encoder files.");
  }
  enabledFs << "1";
}

uint32_t EncoderEqep::read() {
  m_eqepPosFile.seekg(0, std::ios::beg);
  uint32_t encoderValue;
  m_eqepPosFile >> encoderValue;
  return encoderValue;
}

}  // namespace BeagleBoneIO
