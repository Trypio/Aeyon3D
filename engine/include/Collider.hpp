//
//
//

#ifndef AEYON3D_COLLIDER_HPP
#define AEYON3D_COLLIDER_HPP

#include "ECS/Component.hpp"
#include "Bounds.hpp"

namespace aeyon
{
	class Collider : public Component<Collider>
	{
	public:
		~Collider() override = default;
	};
}


#endif
