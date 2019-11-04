//
//
//

#ifndef AEYON3D_COMPONENT_HPP
#define AEYON3D_COMPONENT_HPP

#include <cstddef>
#include <type_traits>

namespace aeyon
{
	struct ComponentTypeIDCounter
	{
		static std::size_t counter;
	};

	/**
	 * Adds a unique component type id trait to the derived class
	 */
	template <typename T>
	struct Component
	{
		virtual ~Component() = default;

		static std::size_t getTypeID()
		{
			static std::size_t id = ComponentTypeIDCounter::counter++;
			return id;
		}
	};

	template <typename T>
	static std::size_t GetComponentTypeID()
	{
		return Component<typename std::remove_const<T>::type>::getTypeID();
	}
}

#endif