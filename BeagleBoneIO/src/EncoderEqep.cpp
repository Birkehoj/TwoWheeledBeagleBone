#include "BeagleBoneIO/EncoderEqep.h"

#include <string>

using BeagleBoneIO::EncoderPosition;
using std::string;

static inline string getFilePath(EncoderPosition pos)
{
	switch (pos)
	{
		case EncoderPosition::first:
			return "/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep";
		case EncoderPosition::second:
			return "/sys/devices/platform/ocp/48302000.epwmss/48302180.eqep";
		case EncoderPosition::third:
			break;  // fall though instead of return to avoid compiler warning
	}
	return "/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep";
}

namespace BeagleBoneIO
{
EncoderEqep::EncoderEqep(EncoderPosition pos)
	: m_eqepPosFile(getFilePath(pos) + "/position")
{
	m_eqepPosFile.exceptions();
	write(0);

	std::fstream enabledFs(getFilePath(pos) + "/enabled");
	enabledFs.exceptions();
	enabledFs << "1";
}

uint32_t EncoderEqep::read()
{
	uint32_t encoderValue;
	m_eqepPosFile >> encoderValue;
	m_eqepPosFile.seekg(0, std::ios::beg);  // Prepare for next operation !!!!!!!!!!!!111111
	return encoderValue;
}

void EncoderEqep::write(uint32_t encoderTicks)
{
	m_eqepPosFile << encoderTicks;
	m_eqepPosFile.seekg(0, std::ios::beg);
}

}  // namespace BeagleBoneIO
