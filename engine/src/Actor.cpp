//
// Created by thors on 07.10.2023.
//

#include "Actor.hpp"

namespace aeyon
{
    aeyon::Actor::Actor()
            : Actor("")
    {
    }

    Actor::Actor(std::string name)
            : m_name(std::move(name)), m_isActive(true)
    {
        addComponent<Transform>();
    }

    Actor::Actor(const Actor& other) :
            m_name(other.m_name), m_isActive(other.m_isActive)
    {
        for (const auto& c : other.m_components)
        {
            m_components.insert(std::make_pair(c.first, std::make_unique<Component>(*c.second)));
        }
    }

    Actor::Actor(Actor&& other) noexcept: Actor()
    {
        swap(*this, other);
    }

    Actor& Actor::operator=(Actor other)
    {
        swap(*this, other);
        return *this;
    }

    void swap(Actor& first, Actor& second) noexcept
    {
        using std::swap;

        swap(first.m_name, second.m_name);
        swap(first.m_components, second.m_components);
        swap(first.m_isActive, second.m_isActive);
    }

    void Actor::setName(std::string name)
    {
        m_name = std::move(name);
    }

    void Actor::setActive(bool isActive)
    {
        m_isActive = isActive;

        for (auto& e : m_components)
        {
            e.second->setActive(isActive);
        }

        for (auto child : getTransform()->getChildren())
        {
            child->setActive(isActive);
        }
    }

    const std::string& Actor::getName() const
    {
        return m_name;
    }

    bool Actor::isActive() const
    {
        return m_isActive;
    }

    const Transform* Actor::getTransform() const
    {
        return getComponent<Transform>();
    }

    Transform* Actor::getTransform()
    {
        return getComponent<Transform>();
    }

}
