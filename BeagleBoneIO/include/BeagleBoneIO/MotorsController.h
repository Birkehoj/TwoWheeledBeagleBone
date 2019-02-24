#ifndef BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_MOTORS_CONTROLLER_H_
#define BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_MOTORS_CONTROLLER_H_

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
	explicit MotorsController(int pwmFrequency = 25000);
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

#endif  // BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_MOTORS_CONTROLLER_H_
