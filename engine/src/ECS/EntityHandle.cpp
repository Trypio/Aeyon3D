//
//
//

#include "ECS/EntityHandle.hpp"

namespace aeyon
{

	aeyon::EntityHandle::EntityHandle(std::shared_ptr <EntityHandleInfo> handleInfo, World* world)
			: m_handleInfo(std::move(handleInfo)), m_world(world)
	{
	}

	void EntityHandle::destroy()
	{
		m_world->destroyEntity(m_handleInfo->entity);
	}

	bool EntityHandle::isValid() const
	{
		return m_handleInfo ? m_handleInfo->isValid : false;
	}

	EntityHandle::operator bool() const
	{
		return isValid();
	}

	bool EntityHandle::operator!() const
	{
		return !*this;
	}

	Entity EntityHandle::get() const
	{
		return m_handleInfo ? m_handleInfo->entity : Entity::Invalid;
	}

	Entity::ID EntityHandle::getID() const
	{
		return get().getID();
	}

	bool operator==(const EntityHandle& lhs, const EntityHandle& rhs)
	{
		return lhs.get() == rhs.get();
	}

	bool operator!=(const EntityHandle& lhs, const EntityHandle& rhs)
	{
		return !(lhs == rhs);
	}
}
