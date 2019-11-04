//
//
//

#ifndef AEYON3D_KEYPRESSEVENT_HPP
#define AEYON3D_KEYPRESSEVENT_HPP

#include "Event/Event.hpp"
#include "Input/KeyCode.hpp"
#include "Input/KeyChar.hpp"
#include "Input/KeyMod.hpp"
#include "Input/KeyAction.hpp"

namespace aeyon
{
	struct KeyboardEvent : Event
	{
		KeyAction action;
		KeyCode keycode;
		KeyMod modifier;
		KeyChar charcode;
		bool repeat;
	};
}

#endif //AEYON3D_KEYPRESSEVENT_HPP
