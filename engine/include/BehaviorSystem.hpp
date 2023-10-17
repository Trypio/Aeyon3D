//
// Created by thors on 08.10.2023.
//

#ifndef AEYON3D_BEHAVIORSYSTEM_HPP
#define AEYON3D_BEHAVIORSYSTEM_HPP

#include "System.hpp"

namespace aeyon
{
    class Input;
    class SceneLoader;

    class BehaviorSystem : public System
    {
    private:
        Input* m_input;
        SceneLoader* m_sceneLoader;
    public:
        BehaviorSystem(Input* input, SceneLoader* sceneLoader);
        void setup() override;
        void start() override;
        void update() override;
        void fixedUpdate() override;
    };
}

#endif //AEYON3D_BEHAVIORSYSTEM_HPP