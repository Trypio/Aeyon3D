//
// Created by thors on 08.10.2023.
//

#ifndef AEYON3D_BEHAVIOR_HPP
#define AEYON3D_BEHAVIOR_HPP

#include "Component.hpp"
#include "Actor.hpp"
#include "BehaviorMeta.hpp"

namespace aeyon
{
    class Transform;

    class Behavior : public Component
    {
    protected:
        Transform* transform;
        Input* input;
        SceneLoader* sceneLoader;

    public:
        Behavior() : transform(getActor()->getTransform()), input(nullptr), sceneLoader(nullptr) {}
        virtual void setup() {};
        virtual void start() {};
        virtual void update() {};
        virtual void fixedUpdate() {};

        void setBehaviorMeta(const BehaviorMeta& behaviorMeta)
        {
            input = behaviorMeta.input;
            sceneLoader = behaviorMeta.sceneLoader;
        };
    };
}

#endif //AEYON3D_BEHAVIOR_HPP
