//
//
//

#include "ECS/Entity.hpp"

namespace aeyon
{
	const Entity Entity::Invalid;

	Entity::Entity(Entity::ID id) : m_id(id)
	{
	}

	Entity::ID Entity::getID() const
	{
		return m_id;
	}


	Entity::operator bool() const
	{
		return m_id != InvalidID;
	}

	bool operator==(const Entity& lhs, const Entity& rhs)
	{
		return lhs.m_id == rhs.m_id;
	}

	bool operator!=(const Entity& lhs, const Entity& rhs)
	{
		return !(lhs == rhs);
	}

	bool operator<(const Entity& lhs, const Entity& rhs)
	{
		return lhs.m_id < rhs.m_id;
	}

	bool operator>(const Entity& lhs, const Entity& rhs)
	{
		return rhs < lhs;
	}

	bool operator<=(const Entity& lhs, const Entity& rhs)
	{
		return !(lhs > rhs);
	}

	bool operator>=(const Entity& lhs, const Entity& rhs)
	{
		return !(rhs < lhs);
	}
}
