//
//
//

#ifndef AEYON3D_COMPONENTINFO_HPP
#define AEYON3D_COMPONENTINFO_HPP

#include "Types.hpp"
#include "ComponentInstance.hpp"
#include "Entity.hpp"

namespace aeyon
{
	template <typename T>
	class ComponentStore;

	/**
	 * This class represents the common data between a ComponentHandle its respective ComponentStore. Thus, if the ECS
	 * triggers a change on the enclosed component, it will be delegated to all references of said component.
	 */
	template <typename T>
	struct ComponentHandleInfo
	{
		Entity entity;
		ComponentStore<T>* store;
		ComponentInstance instance;
		bool isValid;

		ComponentHandleInfo()
		: entity(Entity::Invalid), store(nullptr), instance(ComponentInstance::Invalid), isValid(false)
		{
		}

		ComponentHandleInfo(Entity entity, ComponentStore<T>* store, ComponentInstance instance)
				: entity(entity), store(store), instance(instance), isValid(instance != ComponentInstance::Invalid)
		{
		}
	};
}

#endif
