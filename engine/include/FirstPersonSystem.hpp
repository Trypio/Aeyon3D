//
//
//

#ifndef AEYON3D_FIRSTPERSONSYSTEM_HPP
#define AEYON3D_FIRSTPERSONSYSTEM_HPP

#include "System.hpp"
#include "Input/Input.hpp"
#include "Transform.hpp"
#include "FirstPersonController.hpp"
#include "Time.hpp"

namespace aeyon
{
	class FirstPersonSystem : public System
	{
	private:
		Input* m_input;
		Scene* m_scene;

	public:
		explicit FirstPersonSystem(Scene* scene, Input* input)
		: m_scene(scene), m_input(input)
		{
		}

		void update() override
		{
			for (auto actor : m_scene->getActors())
			{
				auto transform = actor->getComponent<Transform>();
				auto controller = actor->getComponent<FirstPersonController>();

				glm::vec2 mouseMotion = m_input->getMouseMotion();

				transform->rotate({0.0f, controller->m_mouseSensitivity * mouseMotion.x, 0.0f}, Space::World);
				transform->rotate({controller->m_mouseSensitivity * mouseMotion.y, 0.0f, 0.0f});

				if (m_input->isKeyDown(KeyCode::W) || m_input->isKeyDown(KeyCode::Up))
				{
					transform->translate(glm::vec3(0.0f, 0.0f, controller->m_moveSpeed * Time::getDeltaTime()));
				}

				if (m_input->isKeyDown(KeyCode::A) || m_input->isKeyDown(KeyCode::Left))
				{
					transform->translate({-controller->m_moveSpeed * Time::getDeltaTime(), 0.0f, 0.0f});
				}

				if (m_input->isKeyDown(KeyCode::S) || m_input->isKeyDown(KeyCode::Down))
				{
					transform->translate({0.0f, 0.0f, -controller->m_moveSpeed * Time::getDeltaTime()});
				}

				if (m_input->isKeyDown(KeyCode::D) || m_input->isKeyDown(KeyCode::Right))
				{
					transform->translate({controller->m_moveSpeed * Time::getDeltaTime(), 0.0f, 0.0f});
				}

				if (m_input->isKeyDown(KeyCode::LeftShift) || m_input->isKeyDown(KeyCode::RightShift))
				{
					transform->translate({0.0f, controller->m_moveSpeed * Time::getDeltaTime(), 0.0f});
				}

				if (m_input->isKeyDown(KeyCode::LeftControl) || m_input->isKeyDown(KeyCode::RightControl))
				{
					transform->translate({0.0f, -controller->m_moveSpeed * Time::getDeltaTime(), 0.0f});
				}
			}
		}
	};
}

#endif //AEYON3D_FIRSTPERSONSYSTEM_HPP
