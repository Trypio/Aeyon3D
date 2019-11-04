//
//
//

#include "ECS/EntityStore.hpp"
#include "ECS/ECSException.hpp"

namespace aeyon
{
	std::shared_ptr<EntityHandleInfo> EntityStore::createEntity()
	{
		Entity::ID newID;
		if (!m_unusedIDs.empty())
		{
			newID = m_unusedIDs.front();
			m_unusedIDs.pop();
		}
		else
		{
			newID = m_entityCounter++;
		}

		if (m_entityCounter == Entity::Invalid.getID())
		{
			throw ECSException("There is no free entity slot left");
		}

		auto ptr = std::make_shared<EntityHandleInfo>(Entity(newID));

		m_handles[ptr->entity] = ptr;

		return ptr;
	}

	void EntityStore::destroyEntity(const Entity& entity)
	{
		m_unusedIDs.push(entity.getID());

		auto& ptr = m_handles.at(entity);
		ptr->entity = Entity::Invalid;
		ptr->isValid = false;
		ptr.reset();
	}

	std::shared_ptr<EntityHandleInfo> EntityStore::getEntityHandleInfo(const Entity& entity) const
	{
		return m_handles.at(entity);
	}
}

