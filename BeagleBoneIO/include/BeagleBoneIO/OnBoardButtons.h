#pragma once

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
