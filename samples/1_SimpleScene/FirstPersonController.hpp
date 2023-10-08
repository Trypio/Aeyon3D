//
//
//

#ifndef AEYON3D_CHARACTERCONTROLLER_HPP
#define AEYON3D_CHARACTERCONTROLLER_HPP

#include "Component.hpp"

namespace aeyon
{
    class FirstPersonController : public Component
    {
    public:
        explicit FirstPersonController(aeyon::Actor* actor) : Component(actor) {}

        float m_moveSpeed;
        float m_mouseSensitivity;
    };
}



#endif //AEYON3D_CHARACTERCONTROLLER_HPP
