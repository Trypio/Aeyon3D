//
//
//

#ifndef AEYON3D_KEYMOD_HPP
#define AEYON3D_KEYMOD_HPP

#include <cstdint>

namespace aeyon
{
	enum class KeyMod : std::uint32_t
	{
		None = 0x0000,
		LeftControl = 0x0001,
		LeftShift = 0x0002,
		LeftAlt = 0x0040,
		LeftGUI = 0x0080,
		RightControl = 0x0100,
		RightShift = 0x0200,
		RightAlt = 0x0400,
		RightGUI = 0x0800,
		NumLock = 0x1000,
		CapsLock = 0x2000,
		Reserved1 = 0x4000,
		Reserved2 = 0x8000,

		Control = LeftControl | RightControl,
		Shift = LeftShift | RightShift,
		Alt = LeftAlt | RightAlt,
		GUI = LeftGUI | RightGUI
	};
}

#endif //AEYON3D_KEYMOD_HPP
