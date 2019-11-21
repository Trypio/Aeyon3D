//
//
//

#ifndef AEYON3D_COMPONENTINSTANCE_HPP
#define AEYON3D_COMPONENTINSTANCE_HPP

#include <cstddef>
#include "EntityID.hpp"
#include "ComponentID.hpp"

namespace aeyon
{
	struct ComponentInstance
	{
		ComponentID id;
		std::size_t index;

		ComponentInstance() = default;
		ComponentInstance(ComponentID id, std::size_t index) : id(id), index(index) {}
	};
}



#endif //AEYON3D_COMPONENTINSTANCE_HPP
