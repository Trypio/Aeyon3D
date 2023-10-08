//
// Created by thors on 07.10.2023.
//

#include "Component.hpp"

namespace aeyon
{

    Component::Component(Actor* actor) : m_actor(actor), m_isActive(true) {}

    void Component::setActive(bool isActive) { m_isActive = isActive; }

    bool Component::isActive() const { return m_isActive; }
}

