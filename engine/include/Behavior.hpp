//
// Created by thors on 08.10.2023.
//

#ifndef AEYON3D_BEHAVIOR_HPP
#define AEYON3D_BEHAVIOR_HPP

#include "Component.hpp"
#include "Actor.hpp"

namespace aeyon
{
    class Transform;

    class Behavior : Component
    {
    protected:
        Transform* transform;

    public:
        explicit Behavior(Actor* actor) : Component(actor), transform(actor->getTransform()) {}
        virtual void setup() {};
        virtual void start() {};
        virtual void update() {};
        virtual void fixedUpdate() {};
    };
}

#endif //AEYON3D_BEHAVIOR_HPP
