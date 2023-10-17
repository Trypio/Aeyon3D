//
// Created by thors on 16.10.2023.
//

#ifndef AEYON3D_BEHAVIORMETA_HPP
#define AEYON3D_BEHAVIORMETA_HPP

namespace aeyon
{
    class Input;
    class SceneLoader;

    struct BehaviorMeta
    {
        Input* input;
        SceneLoader* sceneLoader;
    };
}

#endif //AEYON3D_BEHAVIORMETA_HPP
