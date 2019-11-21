//
//
//

#ifndef AEYON3D_COLLIDER_HPP
#define AEYON3D_COLLIDER_HPP

#include "ECS/ComponentTypeIndex.hpp"
#include "Bounds.hpp"

namespace aeyon
{
	class Collider : public ComponentTypeIndex<Collider>
	{
	public:
		~Collider() override = default;
	};
}


#endif
