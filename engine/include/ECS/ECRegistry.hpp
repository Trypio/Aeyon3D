//
//
//

#ifndef AEYON3D_ECREGISTRY_HPP
#define AEYON3D_ECREGISTRY_HPP

#include <unordered_map>
#include <array>
#include "Types.hpp"
#include "ComponentInstance.hpp"


namespace aeyon
{
/**
 * A simple bidirectional map which maps entity to components and vice-versa
 */
	class ECRegistry
	{
	private:
		std::unordered_map<EntityID, ComponentID> m_entityToComponent;
		std::unordered_map<ComponentID, EntityID> m_componentToEntity;

	public:
		EntityID getEntityID(const ComponentID& componentID) const;
		ComponentID getComponentID(const EntityID& entityID) const;
		bool insert(const EntityID& entityID, const ComponentID& componentID);
		void eraseEntityID(const EntityID& entityID);
		void eraseComponentID(const ComponentID& componentID);
	};
}


#endif
