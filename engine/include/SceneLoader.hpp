//
// Created on 03.10.2022
//

#ifndef AEYON3D_SCENELOADER_HPP
#define AEYON3D_SCENELOADER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include "Scene.hpp"

namespace aeyon
{
    class SceneLoader
    {
    private:
        std::unordered_map<std::string, Scene> m_scenes;
        Scene* m_activeScene = nullptr;
    public:
        Scene& createScene(const std::string &name);

        Scene& getScene(const std::string &name);

        void setActiveScene(const std::string &name);

        Scene* getActiveScene();
    };
}


#endif //AEYON3D_SCENELOADER_HPP
