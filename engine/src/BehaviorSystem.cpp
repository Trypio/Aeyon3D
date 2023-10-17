//
// Created by thors on 08.10.2023.
//

#include "BehaviorSystem.hpp"
#include "SceneLoader.hpp"
#include "Behavior.hpp"

namespace aeyon
{
    BehaviorSystem::BehaviorSystem(Input* input, SceneLoader* sceneLoader) : m_input(input), m_sceneLoader(sceneLoader)
    {
    }

    void BehaviorSystem::setup()
    {
        for (auto& a : m_sceneLoader->getActiveScene()->getActors())
        {
            auto behavior = a.getComponent<Behavior>();
            if (behavior)
            {
                BehaviorMeta meta {};
                meta.input = m_input;
                meta.sceneLoader = m_sceneLoader;
                behavior->setBehaviorMeta(meta);
                behavior->setup();
            }
        }
    }

    void BehaviorSystem::start()
    {
        for (auto& a : m_sceneLoader->getActiveScene()->getActors())
        {
            auto behavior = a.getComponent<Behavior>();
            if (behavior)
            {
                behavior->start();
            }
        }
    }

    void BehaviorSystem::update()
    {
        for (auto& a : m_sceneLoader->getActiveScene()->getActors())
        {
            auto behavior = a.getComponent<Behavior>();
            if (behavior)
            {
                behavior->update();
            }
        }
    }

    void BehaviorSystem::fixedUpdate()
    {
        for (auto& a : m_sceneLoader->getActiveScene()->getActors())
        {
            auto behavior = a.getComponent<Behavior>();
            if (behavior)
            {
                behavior->fixedUpdate();
            }
        }
    }
}