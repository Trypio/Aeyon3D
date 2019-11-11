//
//
//

#ifndef AEYON3D_COMPONENTHANDLE_HPP
#define AEYON3D_COMPONENTHANDLE_HPP

#include <memory>
#include "ComponentHandleDetails.hpp"

namespace aeyon
{
	/**
   * Represents a reference to a unique component in the world. The handle is automatically invalidated if the
   * component is destroyed.
	 */
	template <typename T>
	class ComponentHandle
	{
	private:
		std::shared_ptr<ComponentHandleDetails<T>> m_details;

	public:
		ComponentHandle()
		: ComponentHandle(std::make_shared<ComponentHandleDetails<T>>())
		{
		}

		explicit ComponentHandle(std::shared_ptr<ComponentHandleDetails<T>> componentDetails)
		: m_details(std::move(componentDetails))
		{
		}

		bool isValid() const
		{
			return m_details->isValid();
		}

		explicit operator bool() const
		{
			return isValid();
		}

		T* get()
		{
			return m_details->isValid() ? m_details->store->getComponent(m_details->instance) : nullptr;
		}

		const T* get() const
		{
			return m_details->isValid() ? m_details->store->getComponent(m_details->instance) : nullptr;
		}

		T& operator*()
		{
			return *get();
		}

		const T& operator*() const
		{
			return *get();
		}

		T* operator->()
		{
			return get();
		}

		const T* operator->() const
		{
			return get();
		}
	};
}


#endif //AEYON3D_COMPONENTHANDLE_HPP
