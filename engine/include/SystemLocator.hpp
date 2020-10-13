//
//
//

#ifndef AEYON3D_SYSTEMLOCATOR_HPP
#define AEYON3D_SYSTEMLOCATOR_HPP

#include <memory>
#include <unordered_map>
#include <typeindex>

namespace aeyon
{
	class System;

	class SystemLocator
	{
	private:
		static std::unordered_map<std::type_index, std::unique_ptr<System>> m_services;

	public:
		template <typename T>
		static T* set(std::unique_ptr<T> service)
		{
			return (m_services[typeid(T)] = std::move(service)).get();
		}

		template <typename T>
		static T* get()
		{
			return static_cast<T*>(m_services[typeid(T)].get());
		}
	};
}

#endif //AEYON3D_SYSTEMLOCATOR_HPP
