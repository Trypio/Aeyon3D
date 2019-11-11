//
//
//

#include "ECS/EntityHandle.hpp"

namespace aeyon
{
	aeyon::EntityHandle::EntityHandle(std::shared_ptr <EntityHandleDetails> details)
			: m_details(std::move(details))
	{
	}

	void EntityHandle::destroy()
	{
		m_details->world->destroyEntity(m_details->entity);
	}

	bool EntityHandle::isValid() const
	{
		return m_details->isValid();
	}

	EntityHandle::operator bool() const
	{
		return isValid();
	}

	Entity EntityHandle::get() const
	{
		return m_details->entity;
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
