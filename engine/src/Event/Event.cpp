//
//
//

#include "Event/Event.hpp"

namespace aeyon
{
	Event::ID Event::currentID = 0;

	Event::ID Event::getNextID()
	{
		return currentID++;
	}

	Event::Event()
			: m_id(Event::getNextID())
	{
	}

	Event::ID Event::getID() const
	{
		return m_id;
	}
}
