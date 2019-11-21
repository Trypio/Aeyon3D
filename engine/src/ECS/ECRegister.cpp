//
//
//

#include "ECS/ECRegister.hpp"

namespace aeyon
{
	EntityID ECRegister::getEntityID(const ComponentID& componentID) const
	{
		const auto it = m_componentToEntity.find(componentID);
		return (it != m_componentToEntity.end()) ? it->second : EntityID();
	}

	ComponentID ECRegister::getComponentID(const EntityID& entityID) const
	{
		const auto it = m_entityToComponent.find(entityID);
		return (it != m_componentToEntity.end()) ? it->second : ComponentID();
	}

	bool ECRegister::insert(const EntityID& entityID, const ComponentID& componentID)
	{
		auto etcIt = m_entityToComponent.find(entityID);
		auto cteIt = m_componentToEntity.find(componentID);

		if (etcIt != m_entityToComponent.end() || cteIt != m_componentToEntity.end())
			return false;
		else
		{
			m_entityToComponent[entityID] = componentID;
			m_componentToEntity[componentID] = entityID;
			return true;
		}
	}

	void ECRegister::eraseEntityID(const EntityID& entityID)
	{
		const auto it = m_entityToComponent.find(entityID);
		if (it != m_entityToComponent.end())
		{
			m_componentToEntity.erase(it->second);
			m_entityToComponent.erase(it);
		}
	}

	void ECRegister::eraseComponentID(const ComponentID& componentID)
	{
		const auto it = m_componentToEntity.find(componentID);
		if (it != m_componentToEntity.end())
		{
			m_entityToComponent.erase(it->second);
			m_componentToEntity.erase(it);
		}
	}
}


