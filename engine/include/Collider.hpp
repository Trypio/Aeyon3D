//
//
//

#ifndef AEYON3D_COLLIDER_HPP
#define AEYON3D_COLLIDER_HPP

#include "Component.hpp"
#include "Bounds.hpp"

namespace aeyon
{
	class Collider : public Component
	{
	public:
		~Collider() override = default;
	};
}


#endif
