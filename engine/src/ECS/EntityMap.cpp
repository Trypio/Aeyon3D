//
//
//

#include "ECS/EntityMap.hpp"

namespace aeyon
{
	Entity EntityMap::getEntity(const ComponentInstance& instance) const
	{
		return m_instanceToEntity.at(instance.getID());
	}

	ComponentInstance EntityMap::getInstance(const Entity& entity) const
	{
		return m_entityToInstance.at(entity);
	}

	void EntityMap::insert(Entity entity, ComponentInstance instance)
	{
		m_entityToInstance[entity] = instance;
		m_instanceToEntity[instance.getID()] = entity;
	}

	void EntityMap::remove(const Entity& entity)
	{
		auto it = m_entityToInstance.find(entity);
		if (it != m_entityToInstance.end())
		{
			m_entityToInstance.erase(entity);
			m_instanceToEntity[it->second.getID()] = Entity::Invalid;
		}
	}
}


