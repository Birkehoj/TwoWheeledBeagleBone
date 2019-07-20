#ifndef BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_MOTORSCONTROLLER_H_
#define BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_MOTORSCONTROLLER_H_

namespace BeagleBoneIO
{
enum class ChannelNumber
{
	all,
	one,
	two,
	three,
	four,
};

class MotorsController
{
public:
	static constexpr int defaultPwmFrequency{25000};
	explicit MotorsController(int pwmFrequency = defaultPwmFrequency);
	~MotorsController();
	MotorsController(const MotorsController &other) = delete;
	MotorsController &operator=(const MotorsController &other) = delete;
	MotorsController(MotorsController &&other) = default;
	MotorsController &operator=(MotorsController &&other) = default;
	// cppcheck-suppress functionStatic
	void set(ChannelNumber ch, double duty);
	// cppcheck-suppress functionStatic
	void breakMotor(ChannelNumber ch);
	// cppcheck-suppress functionStatic
	void enableFreeSpin(ChannelNumber ch);
};
}  // namespace BeagleBoneIO

#endif  // BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_MOTORSCONTROLLER_H_
