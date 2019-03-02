#ifndef BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_ONBOARDBUTTONS_H_
#define BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_ONBOARDBUTTONS_H_

namespace BeagleBoneIO
{
class OnBoardButtons
{
public:
	enum class ButtonType
	{
		pause,
		mode,
	};
	explicit OnBoardButtons(ButtonType /*buttonType*/) {}
};
}  // namespace BeagleBoneIO
#endif  // BEAGLEBONEIO_INCLUDE_BEAGLEBONEIO_ONBOARDBUTTONS_H_
