#ifndef AEYON3D_WINDOWRESIZEEVENT_HPP
#define AEYON3D_WINDOWRESIZEEVENT_HPP

#include "Event/Event.hpp"

namespace aeyon
{
    /**
     * Indicates that the main window has been resized
     */
	struct WindowResizeEvent : Event
	{
		int height, width;
		int viewportHeight, viewportWidth;
	};
}

#endif //AEYON3D_WINDOWRESIZEEVENT_HPP
