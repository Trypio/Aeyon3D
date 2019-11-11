//
//
//

#ifndef AEYON3D_WORLD_HPP
#define AEYON3D_WORLD_HPP

#include "EntityStore.hpp"
#include "Entity.hpp"
#include "ComponentStore.hpp"
#include "ComponentHandle.hpp"
#include <memory>
#include <vector>
#include <bitset>
#include <typeindex>
#include "EntityMap.hpp"
#include "Event/EventSystem.hpp"
#include "Types.hpp"
#include "Component.hpp"

namespace aeyon
{
	class System;
	class EntityHandle;

	/**
	 * The World is where all entities, components and systems reside. It delegates requests for the creation or
	 * destruction of entities/components to the respective Stores and assigns entity instances to systems based on
	 * their component signatures.
	 */
	class World
	{
	private:
		/**
		 * Keeps track of all valid entity ids
		 */
		EntityStore m_entityStore;

		/**
		 * List of systems in registration/update order
		 */
		std::vector<std::unique_ptr<System>> m_systems;

		/**
		 * Vector which holds the component stores for a specific type. The index represents the TypeIndex of a component
		 * and can be retrieved via GetComponentTypeID<T>().
		 */
		mutable std::array<std::unique_ptr<ComponentStoreBase>, NumComponentTypes> m_componentStores;

		/**
		 * Maps entities to bitmasks which represent what components are attached to them
		 */
		std::unordered_map<Entity, Signature> m_entityMasks;

		/**
		 * Vector of bidirectional maps which keep track of entities and their mapped components and vice-versa. The
		 * index represents the TypeIndex of the component and can be retrieved via GetComponentTypeID<T>().
		 */
		std::array<EntityMap, NumComponentTypes> m_entityMaps;

		/**
		 * Retrieves the component store which is assigned to the given type. A new component store of given type is
		 * created if there doesn't exist one yet.
		 *
		 */
		template <typename T>
		ComponentStore<T>* getComponentStore() const
		{
			std::size_t typeID = GetComponentTypeID<T>();

			if (!m_componentStores[typeID])
			{
				m_componentStores[typeID] = std::make_unique<ComponentStore<T>>();
			}

			return static_cast<ComponentStore<T>*>(m_componentStores[typeID].get());
		}

		void addEntityToSystems(const Entity& entity, std::size_t typeID, const Signature& oldMask);
		void removeEntityFromSystems(const Entity& entity, std::size_t typeID, const Signature& oldMask);

	public:
		World();
		World(const World&) = delete;
		World& operator=(const World&) = delete;

	  /*
		 * World event system
	   */
		EventSystem eventSystem;

		/*
		 * Should be called before the first update, but after instantiation
		 */
		void init();

		/**
		 * Called each frame
		 */
		void update();

		/**
		 * Called at a fixed time step
		 */
		void fixedUpdate();

		/**
		 * Called after update() has been called on all systems
		 */
		void lateUpdate();

		/**
		 * Create a new entity
		 */
		EntityHandle createEntity();

		/**
		 * Mark the given entity as destroyed
		 */
		void destroyEntity(const Entity& entity);


		/**
		 * Add a system to the world. System methods are guaranteed to be called in the order they were added to the world.
		 */
		void addSystem(std::unique_ptr<System> system);

		/**
		 * Add the given component to the given entity
		 */
		template <typename T, typename ...P>
		ComponentHandle<T> addComponent(const Entity& entity, P&&... parameters)
		{
			auto store = getComponentStore<T>();
			auto componentInfo = store->createComponent(std::forward<P>(parameters)...);
			componentInfo->owner = entity;

			m_entityMaps[GetComponentTypeID<T>()].insert(entity, componentInfo->instance);
			Signature oldMask = m_entityMasks.at(entity);
			m_entityMasks[entity].set(GetComponentTypeID<T>(), true);

			addEntityToSystems(entity, GetComponentTypeID<T>(), oldMask);

			return ComponentHandle<T>(componentInfo);
		}

		/**
		 * Remove the given component type from the given entity
		 */
		template <typename T>
		void removeComponent(const Entity& entity)
		{
			getComponentStore<T>()->destroyComponent(m_entityMaps[GetComponentTypeID<T>()].getInstance(entity));

			Signature oldMask = m_entityMasks.at(entity);
			m_entityMasks[entity].set(GetComponentTypeID<T>(), false);

			removeEntityFromSystems(entity, GetComponentTypeID<T>(), oldMask);
		}

		template <typename T>
		bool hasComponent(const Entity& entity) const
		{
			return m_entityMasks.at(entity).test(GetComponentTypeID<T>());
		}

		template <typename T>
		ComponentHandle<T> getComponent(const Entity& entity) const
		{
			auto store = getComponentStore<T>();
			auto id = GetComponentTypeID<T>();
			auto instance = m_entityMaps[id].getInstance(entity);
			return ComponentHandle<T>(store->getComponentHandleDetails(instance));
		}
	};
}



#endif //AEYON3D_WORLD_HPP
