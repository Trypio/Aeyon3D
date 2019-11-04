//
//
//

#include "Engine.hpp"
#include <SDL2/SDL.h>
#include "glad/glad.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include "SDLWindow.hpp"
#include "Input/SDLInput.hpp"

#include "Time.hpp"
#include "FirstPersonController.hpp"
#include "FirstPersonSystem.hpp"
#include "CollisionSystem.hpp"
#include "Util.hpp"
#include "Primitive.hpp"
#include "Graphics/Light.hpp"
#include "Input/KeyCode.hpp"
#include "Event/EventSystem.hpp"
#include "ECS/System.hpp"
#include "Graphics/GraphicsSystem.hpp"

namespace aeyon
{
	void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
																const GLchar* message, const void* userParam)
	{
		if (type == GL_DEBUG_TYPE_ERROR_ARB)
			throw std::runtime_error(message);
	}

	void Engine::setup()
	{
	}

	void Engine::start()
	{
		// To be overridden by user
	}

	void Engine::update()
	{
		// To be overridden by user
	}

	void Engine::fixedUpdate()
	{
		// To be overridden by user
	}

	void Engine::lateUpdate()
	{
		// To be overridden by user
	}

	void Engine::run()
	{
		SDL_Init(SDL_INIT_VIDEO);

		m_input = std::make_unique<SDLInput>();
		m_window = std::make_unique<SDLWindow>("Aeyon3D", SDL_WINDOWPOS_CENTERED,
																					 SDL_WINDOWPOS_CENTERED, 1024, 768);
		m_window->makeContextCurrent();
		gladLoadGLLoader(m_window->getProcAddress());

		if (GLAD_GL_ARB_debug_output)
		{
			glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
			glDebugMessageCallbackARB(glDebugCallback, nullptr);

			std::cout << "OpenGL Debug Context initialized" << std::endl;
		}
		else
		{
			std::cout << "ARB_debug_output is not supported on this system" << std::endl;
		}

		m_world = std::make_unique<World>();

		std::unique_ptr<GraphicsSystem> graphics = std::make_unique<GraphicsSystem>(m_window.get());

		m_world->addSystem(std::make_unique<FirstPersonSystem>(m_input.get()));
		m_world->addSystem(std::make_unique<CollisionSystem>());

		m_graphics = graphics.get();
		m_world->addSystem(std::move(graphics));

		m_world->init();

		start();

		while (!m_window->shouldClose())
		{
			Time::update();
			m_input->update();
			update();
			m_world->update();

			lateUpdate();

			m_window->swapBuffers();
		}

		SDL_Quit();
	}
}
