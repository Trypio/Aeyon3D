//
//
//

#ifndef AEYON3D_ENTITYMAP_HPP
#define AEYON3D_ENTITYMAP_HPP

#include <unordered_map>
#include <array>
#include "Entity.hpp"
#include "Types.hpp"
#include "ComponentInstance.hpp"


namespace aeyon
{
/**
 * A simple bidirectional map which maps entity to components and vice-versa
 */
	class EntityMap
	{
	private:
		std::unordered_map<Entity, ComponentInstance> m_entityToInstance;
		std::array<Entity, MaxNumberOfComponents> m_instanceToEntity;

	public:
		Entity getEntity(const ComponentInstance& instance) const;
		ComponentInstance getInstance(const Entity& entity) const;
		void insert(Entity entity, ComponentInstance instance);
		void remove(const Entity& entity);
	};
}


#endif
