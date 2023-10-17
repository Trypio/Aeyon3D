//
//
//

#ifndef AEYON3D_CHARACTERCONTROLLER_HPP
#define AEYON3D_CHARACTERCONTROLLER_HPP

#include "Behavior.hpp"
#include "Time.hpp"

namespace aeyon
{
    class FirstPersonController : public Behavior
    {
    public:
        float m_moveSpeed = 3.0f;
        float m_mouseSensitivity = 0.1f;
        
        void update() override
        {
            for (auto& actor : sceneLoader->getActiveScene()->getActors())
            {
                if (!actor.hasComponent<FirstPersonController>())
                    continue;

                auto transform = actor.getComponent<Transform>();
                auto controller = actor.getComponent<FirstPersonController>();

                glm::vec2 mouseMotion = input->getMouseMotion();

                transform->rotate({controller->m_mouseSensitivity * mouseMotion.y, 0.0f, 0.0f});
                transform->rotate({0.0f, controller->m_mouseSensitivity * mouseMotion.x, 0.0f}, Space::World);

                if (input->getKey(KeyCode::W) || input->getKey(KeyCode::Up) || input->getMouseButton(MouseButton::Mouse4))
                {
                    float speed = controller->m_moveSpeed;
                    if (input->getKey(KeyCode::LeftShift) || input->getKey(KeyCode::RightShift))
                    {
                        speed *= 4.0f;
                    }
                    transform->translate(transform->getForward() * speed * Time::getDeltaTime());
                }

                if (input->getKey(KeyCode::A) || input->getKey(KeyCode::Left))
                {
                    transform->translate(transform->getRight() * -controller->m_moveSpeed * Time::getDeltaTime());
                }

                if (input->getKey(KeyCode::S) || input->getKey(KeyCode::Down))
                {
                    transform->translate(transform->getForward() * -controller->m_moveSpeed * Time::getDeltaTime());
                }

                if (input->getKey(KeyCode::D) || input->getKey(KeyCode::Right))
                {
                    transform->translate(transform->getRight() * controller->m_moveSpeed * Time::getDeltaTime());
                }

                if (input->getKey(KeyCode::Space))
                {
                    transform->translate(transform->getUp() * controller->m_moveSpeed * Time::getDeltaTime());
                }

                if (input->getKey(KeyCode::LeftControl) || input->getKey(KeyCode::RightControl))
                {
                    transform->translate(transform->getUp() * -controller->m_moveSpeed * Time::getDeltaTime());
                }
            }
        }
    };
}

#endif //AEYON3D_CHARACTERCONTROLLER_HPP
