//
//
//

#include "ECS/Entity.hpp"

namespace aeyon
{
	void Entity::destroy()
	{
		m_world->destroyEntity(m_id);
	}

	bool Entity::isValid() const
	{
		return m_world && !m_id.isNil() && m_world->isEntityIDValid(m_id);
	}

	Entity::operator bool() const
	{
		return isValid();
	}

	const EntityID& Entity::getID() const
	{
		return m_id;
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


}
