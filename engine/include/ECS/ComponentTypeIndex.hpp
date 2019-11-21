//
//
//

#ifndef AEYON3D_COMPONENTTYPEINDEX_HPP
#define AEYON3D_COMPONENTTYPEINDEX_HPP

#include <cstddef>
#include <type_traits>

namespace aeyon
{
	struct ComponentTypeCounter
	{
		static std::size_t counter;
	};

	/**
	 * Adds a unique component type ID trait to the deriving class
	 */
	template <typename T>
	struct ComponentTypeIndex
	{
		virtual ~ComponentTypeIndex() = default;

		static std::size_t get()
		{
			static std::size_t id = ComponentTypeCounter::counter++;
			return id;
		}
	};

	/**
	 * Returns the unique ID of the Component with the given type T
	 */
	template <typename T>
	static std::size_t GetComponentTypeIndex()
	{
		return ComponentTypeIndex<typename std::remove_const<T>::type>::get();
	}
}

#endif
