#ifndef AEYON3D_QUITEVENT_HPP
#define AEYON3D_QUITEVENT_HPP

#include "Event/Event.hpp"

namespace aeyon
{
	/**
	 * Dispatching this event terminates the engine.
	 */
	class QuitEvent : public Event
	{
	};
}

#endif //AEYON3D_QUITEVENT_HPP
