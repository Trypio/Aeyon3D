#ifndef AEYON3D_EVENT_HPP
#define AEYON3D_EVENT_HPP

#include "UUID.hpp"

namespace aeyon
{
	/**
	 * Base class of all events.
	 */
	class Event
	{
	private:
		UUID m_guid;

	public:
        Event();
		virtual ~Event() = default;

		const UUID& getGUID() const;
	};
}


#endif //AEYON3D_EVENT_HPP
