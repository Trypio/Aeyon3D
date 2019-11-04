//
//
//

#ifndef AEYON3D_ENTITYHANDLE_HPP
#define AEYON3D_ENTITYHANDLE_HPP

#include "ComponentHandle.hpp"
#include "Entity.hpp"
#include "World.hpp"
#include "EntityHandleInfo.hpp"

namespace aeyon
{
	/**
   * Represents a reference to a unique entity in the world. The handle is automatically invalidated if the
   * entity is destroyed.
	 */
	class EntityHandle
	{
	private:
		std::shared_ptr<EntityHandleInfo> m_handleInfo;
		World* m_world = nullptr;

	public:
		EntityHandle() = default;
		EntityHandle(std::shared_ptr<EntityHandleInfo> handleInfo, World* world);

		/**
		 * Destroys the component and invalidates the handle
		 */
		void destroy();

		bool isValid() const;
		explicit operator bool() const;
		bool operator!() const;

		friend bool operator==(const EntityHandle& lhs, const EntityHandle& rhs);
		friend bool operator!=(const EntityHandle& lhs, const EntityHandle& rhs);

		Entity get() const;
		Entity::ID getID() const;

		/**
		 * Adds a new component of type T to this entity
		 */
		template <typename T, typename ...P>
		ComponentHandle<T> addComponent(P&&... parameters)
		{
			return m_world->addComponent<T>(m_handleInfo->entity, std::forward<P>(parameters)...);
		}

		/**
		 * Removes the component of type T from this entity
		 */
		template <typename T>
		void removeComponent()
		{
			m_world->removeComponent<T>(m_handleInfo->entity);
		}

		template <typename T>
		bool hasComponent() const
		{
			return m_world->hasComponent<T>(m_handleInfo->entity);
		}

		/**
		 * Gets a handle to the component of type T attached to this entity
		 */
		template <typename T>
		ComponentHandle<T> getComponent() const
		{
			return m_world->getComponent<T>(m_handleInfo->entity);
		}
	};
}

namespace std
{
	template<>
	struct hash<aeyon::EntityHandle>
	{
		std::size_t operator()(const aeyon::EntityHandle& e) const
		{
			return std::hash<aeyon::Entity::ID>()(e.getID());
		}
	};
}

#endif
