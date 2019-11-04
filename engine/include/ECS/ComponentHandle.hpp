//
//
//

#ifndef AEYON3D_COMPONENTHANDLE_HPP
#define AEYON3D_COMPONENTHANDLE_HPP

#include <memory>
#include "ComponentHandleInfo.hpp"

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
		std::shared_ptr<ComponentHandleInfo<T>> m_sharedInfo;

	public:
		ComponentHandle()
		: ComponentHandle(std::make_shared<ComponentHandleInfo<T>>())
		{
		}

		explicit ComponentHandle(std::shared_ptr<ComponentHandleInfo<T>> componentInfo)
		: m_sharedInfo(std::move(componentInfo))
		{
		}

		bool isValid() const
		{
			return m_sharedInfo->isValid;
		}

		explicit operator bool() const
		{
			return isValid();
		}

		bool operator!() const
		{
			return !bool();
		}

		T* get()
		{
			return m_sharedInfo->isValid ? m_sharedInfo->store->getComponent(m_sharedInfo->instance) : nullptr;
		}

		const T* get() const
		{
			return m_sharedInfo->isValid ? m_sharedInfo->store->getComponent(m_sharedInfo->instance) : nullptr;
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
