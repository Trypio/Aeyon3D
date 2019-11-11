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
	 * This class represents the shared data between a ComponentHandle and its respective ComponentStore. Thus, if the
	 * ECS triggers a change on the enclosed component, it will be delegated to all references of said component.
	 */
	template <typename T>
	struct ComponentHandleDetails
	{
		ComponentStore<T>* store;
		ComponentInstance instance;
		Entity owner;

		ComponentHandleDetails()
		:  store(nullptr), instance(ComponentInstance::Invalid), owner(Entity::Invalid)
		{
		}

		ComponentHandleDetails(ComponentStore<T>* store, ComponentInstance instance, Entity owner)
				: store(store), instance(instance), owner(owner)
		{
		}

		bool isValid() const
		{
			return store && instance != ComponentInstance::Invalid && owner != Entity::Invalid;
		}
	};
}

#endif
