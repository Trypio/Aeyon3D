//
// Created by thors on 07.10.2023.
//

#include "Component.hpp"

namespace aeyon
{

    Component::Component() : m_actor(nullptr), m_isActive(true) {}

    void Component::setActive(bool isActive) { m_isActive = isActive; }
    bool Component::isActive() const { return m_isActive; }
    void Component::setActor(Actor* actor) { m_actor = actor; }
    const Actor* Component::getActor() const { return m_actor; }
    Actor* Component::getActor() { return m_actor; }
}
