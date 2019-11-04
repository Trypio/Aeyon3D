//
//
//

#ifndef AEYON3D_CHARACTERCONTROLLER_HPP
#define AEYON3D_CHARACTERCONTROLLER_HPP

#include "ECS/Component.hpp"

namespace aeyon
{
	class FirstPersonController : public Component<FirstPersonController>
	{
	public:
		float m_moveSpeed;
		float m_mouseSensitivity;
	};
}


#endif //AEYON3D_CHARACTERCONTROLLER_HPP
