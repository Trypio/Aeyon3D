//
//
//

#ifndef AEYON3D_WORLD_HPP
#define AEYON3D_WORLD_HPP

#include "EntityID.hpp"
#include "ComponentStore.hpp"
#include <vector>
#include <bitset>
#include <typeindex>
#include "Types.hpp"
#include "ComponentTypeIndex.hpp"
#include <memory>
#include "ECRegistry.hpp"

namespace aeyon
{
	class System;
	class EventSystem;

	/**
	 * The World is where all entities, components and systems reside. It delegates requests for the creation or
	 * destruction of entities/components to the respective Stores and assigns entity instances to systems based on
	 * their component signatures.
	 */
	class World
	{
	private:
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
		std::unordered_map<EntityID, Signature> m_entityMasks;

		/**
		 * Vector of bidirectional maps which keep track of entities and their mapped components and vice-versa. The
		 * index represents the TypeIndex of the component and can be retrieved via GetComponentTypeID<T>().
		 */
		std::array<ECRegistry, NumComponentTypes> m_ecRegistries;

		/**
		 * Retrieves the component store which is assigned to the given type. A new component store of given type is
		 * created if there doesn't exist one yet.
		 */
		template <typename T>
		ComponentStore<T>* getComponentStoreForType() const;

		void addEntityToSystems(const EntityID& entityID, std::size_t typeID, const Signature& oldMask);
		void removeEntityFromSystems(const EntityID& entityID, std::size_t typeID, const Signature& oldMask);

	public:
		explicit World(EventSystem* eventSystem);
		World(const World&) = delete;
		World& operator=(const World&) = delete;
		~World();

	  /**
		 * World event system
	   */
		EventSystem* eventSystem;

		/**
		 * Use this to setup references, register event handlers etc.
		 */
		void setup();

		/**
		 * Should be called before the first update, but after instantiation
		 */
		void start();

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
		 * Create a new entity with no components attached to it
		 */
		EntityID createEntity();

		/**
		 * Destroys the given entity and all of its components
		 */
		void destroyEntity(const EntityID& entityID);

		/**
		 * Checks if the given entity exists within the world
		 */
		bool isEntityValid(const EntityID& entityID) const;

		/**
		 * Adds a system to the world. System methods are guaranteed to be called in the order they were added to the world.
		 */
		void addSystem(std::unique_ptr<System> system);

		/**
		 * Creates and adds a new component to the given entity
		 */
		template <typename T, typename ...P>
		ComponentID addComponent(const EntityID& entityID, P&&... parameters);

		/**
		 *
		 */
		template <typename T>
		ComponentID copyComponent(const EntityID& dstEntityID, const EntityID& srcEntityID);

		template <typename T>
		ComponentID moveComponent(const EntityID& dstEntityID, const EntityID& srcEntityID);

		template <typename T>
		void removeComponent(const EntityID& entityID);

		template <typename T>
		bool hasComponent(const EntityID& entityID) const;

		template <typename T>
		ComponentID getComponentID(const EntityID& entityID) const;

		template <typename T>
		T* getComponent(const ComponentID& componentID);

		template <typename T>
		const T* getComponent(const ComponentID& componentID) const;

		template <typename T>
		EntityID getOwner(const ComponentID& componentID) const;

		template <typename T>
		bool isComponentIDValid(const ComponentID& componentID) const;
	};

	// Template method implementations
	//--------------------------------------------------------------------------------------------------------------------
	template<typename T, typename... P>
	ComponentID World::addComponent(const EntityID& entityID, P&& ... parameters)
	{
		if (hasComponent<T>(entityID))
			return ComponentID();

		auto store = getComponentStoreForType<T>();
		auto instance = store->createComponent(std::forward<P>(parameters)...);
		auto typeIndex = GetComponentTypeIndex<T>();

		m_ecRegistries[typeIndex].insert(entityID, instance.id);

		Signature oldMask = m_entityMasks[entityID];
		m_entityMasks[entityID].set(typeIndex, true);

		addEntityToSystems(entityID, typeIndex, oldMask);

		return instance.id;
	}

	template <typename T>
	ComponentID World::copyComponent(const EntityID& dstEntityID, const EntityID& srcEntityID)
	{
		if (hasComponent<T>(dstEntityID))
			return removeComponent<T>(dstEntityID);

		auto store = getComponentStoreForType<T>();
		auto instance = store->copyComponent(getComponentID<T>(srcEntityID));
		auto typeIndex = GetComponentTypeIndex<T>();

		m_ecRegistries[typeIndex].insert(dstEntityID, instance.id);

		Signature oldMask = m_entityMasks[dstEntityID];
		m_entityMasks[dstEntityID].set(typeIndex, true);

		addEntityToSystems(dstEntityID, typeIndex, oldMask);

		return instance.id;
	}

	template <typename T>
	ComponentID World::moveComponent(const EntityID& dstEntityID, const EntityID& srcEntityID)
	{
		if (hasComponent<T>(dstEntityID) || !hasComponent<T>(srcEntityID))
			return ComponentID();

		auto typeIndex = GetComponentTypeIndex<T>();

		// Remove data about old entity
		Signature oldMask = m_entityMasks[srcEntityID];
		m_entityMasks[srcEntityID].set(typeIndex, false);
		removeEntityFromSystems(srcEntityID, typeIndex, oldMask);
		m_ecRegistries[typeIndex].eraseEntityID(srcEntityID);

		// Add data about new entity
		oldMask = m_entityMasks[dstEntityID];
		m_entityMasks[dstEntityID].set(typeIndex, true);
		addEntityToSystems(dstEntityID, typeIndex, oldMask);
		m_ecRegistries[typeIndex].insert(dstEntityID, componentID);

		return componentID;
	}

	template<typename T>
	void World::removeComponent(const EntityID& entityID)
	{
		if (!hasComponent<T>(entityID))
			return;

		auto componentID = m_ecRegistries[GetComponentTypeIndex<T>()].getComponentID(entityID);
		auto store = getComponentStoreForType<T>();
		auto instance = store->getComponentInstance(componentID);

		Signature oldMask = m_entityMasks[entityID];
		m_entityMasks[entityID].set(GetComponentTypeIndex<T>(), false);

		removeEntityFromSystems(entityID, GetComponentTypeIndex<T>(), oldMask);

		store->destroyComponent(componentID);

		m_ecRegistries[GetComponentTypeIndex<T>()].eraseEntityID(entityID);
	}

	template<typename T>
	ComponentID World::getComponentID(const EntityID& entityID) const
	{
		auto componentIndex = GetComponentTypeIndex<T>();
		return m_ecRegistries[componentIndex].getComponentID(entityID);
	}

	template<typename T>
	bool World::hasComponent(const EntityID& entityID) const
	{
		const auto it = m_entityMasks.find(entityID);
		return (it != m_entityMasks.end()) ? it->second.test(GetComponentTypeIndex<T>()) : false;
	}

	template<typename T>
	T* World::getComponent(const ComponentID& componentID)
	{
		return getComponentStoreForType<T>()->getComponent(componentID);
	}

	template<typename T>
	const T* World::getComponent(const ComponentID& componentID) const
	{
		return getComponentStoreForType<T>()->getComponent(componentID);
	}

	template <typename T>
	EntityID World::getOwner(const ComponentID& componentID) const
	{
		return m_ecRegistries[GetComponentTypeIndex<T>()].getEntityID(componentID);
	}

	template <typename T>
	bool World::isComponentIDValid(const ComponentID& componentID) const
	{
		return !getComponentStoreForType<T>()->getComponentInstance(componentID).id.isNil();
	}

	template<typename T>
	ComponentStore<T>* World::getComponentStoreForType() const
	{
		std::size_t typeIndex = GetComponentTypeIndex<T>();

		if (!m_componentStores[typeIndex])
		{
			m_componentStores[typeIndex] = std::make_unique<ComponentStore<T>>();
		}

		return static_cast<ComponentStore<T>*>(m_componentStores[typeIndex].get());
	}
}

#endif //AEYON3D_WORLD_HPP
