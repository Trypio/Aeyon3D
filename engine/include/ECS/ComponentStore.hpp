//
//
//

#ifndef AEYON3D_COMPONENTSTORE_HPP
#define AEYON3D_COMPONENTSTORE_HPP

#include <array>
#include <queue>
#include <memory>
#include "ComponentStoreBase.hpp"
#include "ComponentHandleDetails.hpp"
#include "ECSException.hpp"

namespace aeyon
{
	/**
	 * Creates and manages the lifetime of ECS components.
	 */
	template <typename T>
	class ComponentStore : public ComponentStoreBase
	{
	private:
		ComponentInstance createInstance()
		{
			ComponentInstance newInstance;
			if (!m_unusedInstances.empty())
			{
				newInstance = ComponentInstance(m_unusedInstances.front());
				m_unusedInstances.pop();
			}
			else
			{
				newInstance = ComponentInstance(m_instanceCounter++);
			}

			return newInstance;
		}

		std::array<T, MaxNumberOfComponents> m_components;
		ComponentInstance::ID m_instanceCounter = 1;
		std::queue<ComponentInstance::ID> m_unusedInstances;
		std::array<std::shared_ptr<ComponentHandleDetails<T>>, MaxNumberOfComponents> m_componentHandles;


	public:
		ComponentStore() = default;
		ComponentStore(const ComponentStore&) = delete;
		ComponentStore& operator=(const ComponentStore&) = delete;

		/**
		 * Creates a new component and returns unique information about it as a shared pointer
		 */
		template <typename ...P>
		std::shared_ptr<ComponentHandleDetails<T>> createComponent(P&& ... parameters)
		{
			ComponentInstance newInstance = createInstance();

			if (!newInstance)
			{
				throw ECSException("Component ID overflow");
			}

			if (newInstance.getID() >= MaxNumberOfComponents)
			{
				throw ECSException("Reached maximum number of components for this component type");
			}

			m_components[newInstance.getID()] = T(std::forward<P>(parameters)...);

			auto ptr = std::make_shared<ComponentHandleDetails<T>>(this, newInstance, Entity::Invalid);
			m_componentHandles[newInstance.getID()] = ptr;

			return ptr;
		}

		/**
		 * Copies the component with the given instance number. The owning entity of the copied component is set to
		 * invalid! Make sure that the component implements at least a copy constructor.
		 */
		template <typename ...P>
		std::shared_ptr<ComponentHandleDetails<T>> copyComponent(const ComponentInstance& srcInstance)
		{
			if (!srcInstance)
			{
				throw ECSException("The component instance is invalid and can't be copied");
			}

			if (srcInstance.getID() >= MaxNumberOfComponents)
			{
				throw ECSException("The component instance you try to destroy is greater than the largest component ID");
			}

			ComponentInstance newInstance = createInstance();

			if (!newInstance)
			{
				throw ECSException("Component ID overflow");
			}

			if (newInstance.getID() >= MaxNumberOfComponents)
			{
				throw ECSException("Reached maximum number of components for this component type");
			}

			m_components[newInstance] = T(m_components[srcInstance]);

			auto ptr = std::make_shared<ComponentHandleDetails<T>>(Entity::Invalid, this, newInstance);
			m_componentHandles[newInstance] = ptr;

			return ptr;
		}

		/**
		 * Destroys the component with the given instance number and invalidates all shared information
		 */
		void destroyComponent(const ComponentInstance& instance)
		{
			if (!instance)
			{
				throw ECSException("The component instance is invalid and can't be destroyed");
			}

			if (instance.getID() >= MaxNumberOfComponents)
			{
				throw ECSException("The component instance you try to destroy is greater than the largest component ID");
			}

			m_unusedInstances.push(instance.getID());
			m_components[instance.getID()] = T();
			auto& ptr = m_componentHandles[instance.getID()];
			ptr->owner = Entity::Invalid;
			ptr->store = nullptr;
			ptr->instance = ComponentInstance::Invalid;
			ptr.reset();
		}

		/**
		 * Gets a pointer to the component with the given instance ID
		 */
		T* getComponent(const ComponentInstance& instance)
		{
			if (!instance)
			{
				throw ECSException("The component instance  ID is invalid");
			}

			if (instance.getID() >= MaxNumberOfComponents)
			{
				throw ECSException("The component instance ID is greater than the largest component");
			}

			return &m_components[instance.getID()];
		}

		const T* getComponent(const ComponentInstance& instance) const
		{
			return getComponent(instance);
		}

		std::shared_ptr<ComponentHandleDetails<T>> getComponentHandleDetails(const ComponentInstance& instance) const
		{
			if (!instance)
			{
				throw ECSException("The component instance is invalid");
			}

			if (instance.getID() >= MaxNumberOfComponents)
			{
				throw ECSException("The component instance ID is greater than the largest component");
			}

			return m_componentHandles[instance.getID()];
		}
	};
}


#endif
