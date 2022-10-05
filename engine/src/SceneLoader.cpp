//
// Created on 03.10.2022.
//

#include "SceneLoader.hpp"
namespace aeyon
{
    Scene& SceneLoader::createScene(const std::string &name)
    {
        return m_scenes.emplace(name, name).first->second;
    }

    Scene& SceneLoader::getScene(const std::string &name)
    {
        return m_scenes.at(name);
    }

    void SceneLoader::setActiveScene(const std::string &name)
    {
        m_activeScene = &getScene(name);
    }

    Scene* SceneLoader::getActiveScene()
    {
        return m_activeScene;
    }
}
