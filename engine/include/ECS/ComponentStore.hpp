//
//
//

#ifndef AEYON3D_COMPONENTSTORE_HPP
#define AEYON3D_COMPONENTSTORE_HPP

#include <array>
#include <queue>
#include "ComponentStoreBase.hpp"
#include "ComponentInstance.hpp"
#include "ComponentID.hpp"
#include "Types.hpp"

namespace aeyon
{
	/**
	 * The ComponentStore is responsible for managing creating and deleting all components of the given type T.
	 * All components are kept in an array of size MaxNumberOfComponents. A given valid ComponentID can be resolved
	 * into the respective array index.
	 */
	template <typename T>
	class ComponentStore : public ComponentStoreBase
	{
	private:
		std::array<T, MaxNumberOfComponents> m_components;
		std::size_t m_indexCounter = 0;
		std::queue<std::size_t> m_unusedIndices;
		std::unordered_map<ComponentID, ComponentInstance> m_instances;

		ComponentInstance createInstance();
		
	public:
		ComponentStore() = default;
		ComponentStore(const ComponentStore&) = delete;
		ComponentStore& operator=(const ComponentStore&) = delete;

		/**
		 * Returns the component instance information for the given component ID.
		 * If there is no component with the given ID, the returned instance will carry an invalid ID field.
		 */
		ComponentInstance getComponentInstance(const ComponentID& id) const;

		/**
		 * Creates a new component
		 */
		template <typename ...P>
		ComponentInstance createComponent(P&& ... parameters);

		/**
		 * Copies the component to a given owner. Make sure that the component implements at least a copy constructor.
		 * If there is no component with the given ID, the returned instance will carry an invalid ID field.
		 */
		ComponentInstance copyComponent(const ComponentID& srcID) override;


		/**
		 * Destroys the component with the given instance number
		 */
		void destroyComponent(const ComponentID& id) override;

		/**
		 * Gets a pointer to the component with the given component ID.
		 * If there is no component with the given ID, the null pointer will be returned.
		 */
		T* getComponent(const ComponentID& id);
		const T* getComponent(const ComponentID& id) const;
	};

	template<typename T>
	ComponentInstance ComponentStore<T>::createInstance()
	{
		ComponentInstance newInstance;

		newInstance.id = ComponentID::generate();

		if (!m_unusedIndices.empty())
		{
			newInstance.index = m_unusedIndices.front();
			m_unusedIndices.pop();
		}
		else
		{
			newInstance.index = m_indexCounter++;
		}

		return newInstance;
	}
	
	template<typename T>
	ComponentInstance ComponentStore<T>::getComponentInstance(const ComponentID& id) const
	{
		const auto it = m_instances.find(id);
		if (it == m_instances.end())
			return ComponentInstance();
		else
			return it->second;
	}

	template<typename T>
	template<typename... P>
	ComponentInstance ComponentStore<T>::createComponent(P&& ... parameters)
	{
		ComponentInstance newInstance = createInstance();
		m_components[newInstance.index] = T(std::forward<P>(parameters)...);
		m_instances[newInstance.id] = newInstance;

		return newInstance;
	}

	template<typename T>
	ComponentInstance ComponentStore<T>::copyComponent(const ComponentID& srcID)
	{
		const auto it = m_instances.find(srcID);
		if (it == m_instances.end())
		{
			return ComponentInstance();
		}
		else
		{
			ComponentInstance newInstance = createInstance();

			m_components[newInstance.index] = T(m_components[it->second.index]);
			m_instances[newInstance.id] = newInstance;

			return newInstance;
		}
	}

	template<typename T>
	void ComponentStore<T>::destroyComponent(const ComponentID& id)
	{
		auto it = m_instances.find(id);

		if (it != m_instances.end())
		{
			std::size_t index = it->second.index;
			m_unusedIndices.push(index);
			m_components[index] = T();
			m_instances.erase(id);
		}
	}

	template<typename T>
	T* ComponentStore<T>::getComponent(const ComponentID& id)
	{
		const auto it = m_instances.find(id);
		return (it != m_instances.end()) ? &m_components[it->second.index] : nullptr;
	}

	template<typename T>
	const T* ComponentStore<T>::getComponent(const ComponentID& id) const
	{
		const auto it = m_instances.find(id);
		return (it != m_instances.end()) ? &m_components[it->second.index] : nullptr;
	}
}


#endif
