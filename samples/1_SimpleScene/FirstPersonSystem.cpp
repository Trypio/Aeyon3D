//
// Created on 04.10.2022.
//

#include "FirstPersonSystem.hpp"
#include "SceneLoader.hpp"
#include "Input/Input.hpp"
#include "FirstPersonController.hpp"
#include "Time.hpp"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

using namespace aeyon;

FirstPersonSystem::FirstPersonSystem(SceneLoader* sceneLoader, Input* input)
        : m_sceneLoader(sceneLoader), m_input(input)
{
}

void FirstPersonSystem::update() {
    for (auto& actor : m_sceneLoader->getActiveScene()->getActors())
    {
        if (!actor.hasComponent<FirstPersonController>())
            continue;

        auto transform = actor.getComponent<Transform>();
        auto controller = actor.getComponent<FirstPersonController>();

        glm::vec2 mouseMotion = m_input->getMouseMotion();

        transform->rotate({controller->m_mouseSensitivity * mouseMotion.y, 0.0f, 0.0f});
        transform->rotate({0.0f, controller->m_mouseSensitivity * mouseMotion.x, 0.0f}, Space::World);

        if (m_input->getKey(KeyCode::W) || m_input->getKey(KeyCode::Up) || m_input->getMouseButton(MouseButton::Mouse4))
        {
            float speed = controller->m_moveSpeed;
            if (m_input->getKey(KeyCode::LeftShift) || m_input->getKey(KeyCode::RightShift))
            {
                speed *= 4.0f;
            }
            transform->translate(transform->getForward() * speed * Time::getDeltaTime());
        }

        if (m_input->getKey(KeyCode::A) || m_input->getKey(KeyCode::Left))
        {
            transform->translate(transform->getRight() * -controller->m_moveSpeed * Time::getDeltaTime());
        }

        if (m_input->getKey(KeyCode::S) || m_input->getKey(KeyCode::Down))
        {
            transform->translate(transform->getForward() * -controller->m_moveSpeed * Time::getDeltaTime());
        }

        if (m_input->getKey(KeyCode::D) || m_input->getKey(KeyCode::Right))
        {
            transform->translate(transform->getRight() * controller->m_moveSpeed * Time::getDeltaTime());
        }

        if (m_input->getKey(KeyCode::Space))
        {
            transform->translate(transform->getUp() * controller->m_moveSpeed * Time::getDeltaTime());
        }

        if (m_input->getKey(KeyCode::LeftControl) || m_input->getKey(KeyCode::RightControl))
        {
            transform->translate(transform->getUp() * -controller->m_moveSpeed * Time::getDeltaTime());
        }
    }
}
