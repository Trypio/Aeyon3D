//
//
//

#ifndef AEYON3D_COMPONENT_HPP
#define AEYON3D_COMPONENT_HPP

#include "ComponentID.hpp"

namespace aeyon
{
	// Forward Declarations
	class World;
	class Entity;

	template <typename T>
	bool operator==(const Component<T>& lhs, const Component<T>& rhs);
	template <typename T>
	bool operator!=(const Component<T>& lhs, const Component<T>& rhs);
	template <typename T>
	bool operator<(const Component<T>& lhs, const Component<T>& rhs);

	/**
   * Represents a reference to a unique component within the world
	 */
	template <typename T>
	class Component
	{
	private:
		ComponentID m_id;
		World* m_world;
		
	public:
		Component();
		Component(ComponentID id, World* world);

		bool isValid() const;
		explicit operator bool() const;

		friend bool operator== <>(const Component<T>& lhs, const Component<T>& rhs);
		friend bool operator!= <>(const Component<T>& lhs, const Component<T>& rhs);
		friend bool operator< <>(const Component<T>& lhs, const Component<T>& rhs);

		ComponentID getID() const;
		Entity getOwner() const;

		T* get();
		const T* get() const;
		T& operator*();
		T* operator->();
		const T& operator*() const;
		const T* operator->() const;
	};
}

// Implementation
//----------------------------------------------------------------------------------------------------------------------

#include "World.hpp"
#include "Entity.hpp"

namespace aeyon
{
	template<typename T>
	Component<T>::Component() : m_world(nullptr) {}

	template<typename T>
	Component<T>::Component(ComponentID id, World* world) : m_id(id), m_world(world) {}

	template<typename T>
	ComponentID Component<T>::getID() const
	{
		return m_id;
	}

	template<typename T>
	T* Component<T>::get()
	{
		return m_world->getComponent<T>(m_id);
	}

	template<typename T>
	const T* Component<T>::get() const
	{
		return m_world->getComponent<T>(m_id);
	}

	template<typename T>
	Entity Component<T>::getOwner() const
	{
		return Entity(m_world->getOwner<T>(m_id), m_world);
	}

	template <typename T>
	bool Component<T>::isValid() const
	{
		return m_world && !m_id.isNil() && m_world->isComponentIDValid<T>(m_id);
	}

	template <typename T>
	Component<T>::operator bool() const
	{
		return isValid();
	}

	template <typename T>
	bool operator==(const Component<T>& lhs, const Component<T>& rhs)
	{
		return lhs.m_id == rhs.m_id;
	}

	template <typename T>
	bool operator!=(const Component<T>& lhs, const Component<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator<(const Component<T>& lhs, const Component<T>& rhs)
	{
		return lhs.m_id < rhs.m_id;
	}

	template<typename T>
	T& Component<T>::operator*()
	{
		return *get();
	}

	template<typename T>
	T* Component<T>::operator->()
	{
		return get();
	}

	template<typename T>
	const T& Component<T>::operator*() const
	{
		return *get();
	}

	template<typename T>
	const T* Component<T>::operator->() const
	{
		return get();
	}
}


#endif //AEYON3D_COMPONENT_HPP
