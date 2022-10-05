//
//
//

#ifndef AEYON3D_FIRSTPERSONSYSTEM_HPP
#define AEYON3D_FIRSTPERSONSYSTEM_HPP

#include "System.hpp"

namespace aeyon
{
    class Input;
    class SceneLoader;
}

class FirstPersonSystem : public aeyon::System
{
private:
    aeyon::Input* m_input;
    aeyon::SceneLoader* m_sceneLoader;

public:
    FirstPersonSystem(aeyon::SceneLoader* sceneLoader, aeyon::Input* input);

    void update() override;
};


#endif //AEYON3D_FIRSTPERSONSYSTEM_HPP
