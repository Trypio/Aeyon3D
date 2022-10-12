//
//
//

#include "Event/Event.hpp"

namespace aeyon
{
    Event::Event() : m_guid(UUID::generate())
    {
    }

	const UUID& Event::getGUID() const
	{
		return m_guid;
	}
}
