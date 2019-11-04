//
//
//

#ifndef AEYON3D_EVENT_HPP
#define AEYON3D_EVENT_HPP

#include <cstdint>

namespace aeyon
{
	/**
	 * Base class of all events
	 */
	class Event
	{
	public:
		using ID = std::uint32_t;

	private:
		static ID currentID;

		static ID getNextID();

		ID m_id;

	public:
		Event();
		virtual ~Event() = default;

		ID getID() const;
	};
}


#endif //AEYON3D_EVENT_HPP
