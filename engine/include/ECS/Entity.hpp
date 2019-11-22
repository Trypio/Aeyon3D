//
//
//

#ifndef AEYON3D_ENTITY_HPP
#define AEYON3D_ENTITY_HPP

#include "EntityID.hpp"

namespace aeyon
{
	// Forward declarations
	class World;
	template <typename T>
	class Component;


	/**
   * Represents a reference to a unique entity in the world. The handle is automatically invalidated if the
   * entity is destroyed.
	 */
	class Entity
	{
	private:
		EntityID m_id;
		World* m_world;

	public:
		Entity() : m_world(nullptr) {}
		Entity(EntityID id, World* world) : m_id(id), m_world(world) {}

		/**
		 * Destroys the component and invalidates the handle
		 */
		void destroy();

		bool isValid() const;
		explicit operator bool() const;

		friend bool operator==(const Entity& lhs, const Entity& rhs);
		friend bool operator!=(const Entity& lhs, const Entity& rhs);
		friend bool operator<(const Entity& lhs, const Entity& rhs);

		const EntityID& getID() const;

		/**
		 * Adds a new component of type T to this entity
		 */
		template <typename T, typename ...P>
		Component<T> addComponent(P&&... parameters);

		template <typename T>
		Component<T> copyComponent(const Component<T>& component);

		template <typename T>
		Component<T> moveComponent(const Component<T>& component);

		/**
		 * Removes the component of type T from this entity
		 */
		template <typename T>
		void removeComponent();

		/**
		 * Checks if the entity owns a component of the given type
		 */
		template <typename T>
		bool hasComponent() const;

		/**
		 * Gets a handle to the component of type T attached to this entity
		 */
		template <typename T>
		Component<T> getComponent() const;
	};
}

// Implementation
//----------------------------------------------------------------------------------------------------------------------

#include "World.hpp"
#include "Component.hpp"

namespace aeyon
{
	template<typename T, typename... P>
	Component<T> Entity::addComponent(P&& ... parameters)
	{
		return Component<T>(m_world->addComponent<T>(m_id, std::forward<P>(parameters)...), m_world);
	}

	template<typename T>
	Component<T> Entity::copyComponent(const Component<T>& component)
	{
		return Component<T>(m_world->copyComponent<T>(m_id, component.getID()), m_world);
	}

	template<typename T>
	Component<T> Entity::moveComponent(const Component<T>& component)
	{
		return Component<T>(m_world->moveComponent<T>(m_id, component.getOwner().getID(), component.getID()), m_world);
	}

	template<typename T>
	void Entity::removeComponent()
	{
		m_world->removeComponent<T>(m_id);
	}

	template <typename T>
	bool Entity::hasComponent() const
	{
		return m_world->hasComponent<T>(m_id);
	}

	template <typename T>
	Component<T> Entity::getComponent() const
	{
		return Component<T>(m_world->getComponentID<T>(m_id), m_world);
	}
}

#endif
