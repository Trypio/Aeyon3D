//
//
//

#ifndef AEYON3D_CHARACTERCONTROLLER_HPP
#define AEYON3D_CHARACTERCONTROLLER_HPP

#include "Component.hpp"


class FirstPersonController : public aeyon::Component
{
public:
    float m_moveSpeed;
    float m_mouseSensitivity;
};



#endif //AEYON3D_CHARACTERCONTROLLER_HPP
