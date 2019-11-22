//
// Created by thors on 21.11.2019.
//

#ifndef AEYON3D_WINDOWRESIZEEVENT_HPP
#define AEYON3D_WINDOWRESIZEEVENT_HPP

#include "Event.hpp"

namespace aeyon
{
	struct WindowResizeEvent : Event
	{
		int height, width;
		int viewportHeight, viewportWidth;
	};
}

#endif //AEYON3D_WINDOWRESIZEEVENT_HPP
