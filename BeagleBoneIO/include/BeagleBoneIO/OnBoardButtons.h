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
	explicit OnBoardButtons(ButtonType) {}
};
}  // namespace BeagleBoneIO
