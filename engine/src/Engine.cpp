//
//
//

#define GLM_ENABLE_EXPERIMENTAL

#include "Engine.hpp"
#include "Time.hpp"
#include "Graphics/GraphicsSystem.hpp"
#include "Input/SDLInput.hpp"
#include "Graphics/SDLWindow.hpp"
#include "GUI/GUISystem.hpp"
#include <SDL2/SDL.h>
#include <spdlog/spdlog.h>

namespace aeyon
{
	void Engine::setup()
	{
		// To be overridden by the user
	}

	void Engine::start()
	{
		// To be overridden by the user
	}

	void Engine::update()
	{
		// To be overridden by the user
	}

	void Engine::fixedUpdate()
	{
		// To be overridden by the user
	}

	void Engine::lateUpdate()
	{
		// To be overridden by the user
	}

	void Engine::run()
	{
        spdlog::set_level(spdlog::level::debug);
        spdlog::info("Welcome to Aeyon3D");

		SDL_Init(SDL_INIT_VIDEO);

		input = std::make_unique<SDLInput>();

		// Query display mode for fullscreen initialization (or setting custom refresh rate)
//		SDL_DisplayMode displayMode;
//		SDL_GetCurrentDisplayMode(0, &displayMode);
//		std::cout << "Native: " << displayMode.w << " x " << displayMode.h << " @ " << displayMode.refresh_rate << "hz" << "\n";

		window = std::make_unique<SDLWindow>(
				"Aeyon3D",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				1024, 768,
				SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
		);

		//sdlWindow->setWindowMode(Window::WindowMode::Fullscreen);

		graphics = std::make_unique<GraphicsSystem>(&sceneLoader, dynamic_cast<SDLWindow*>(window.get()));
		gui = std::make_unique<GUISystem>(graphics.get());
        behaviors = std::make_unique<BehaviorSystem>(&sceneLoader);


		graphics->setup();
		gui->setup();
        setup();
        behaviors->setup();


		graphics->start();
		gui->start();
        start();
        behaviors->setup();


		while (!window->shouldClose())
		{
            Time::update();
            m_eventSystem.update();
			input->update();
			update();
            behaviors->update();
			graphics->update();
            gui->update();

			lateUpdate();

			window->swapBuffers();
		}

		SDL_Quit();
	}
}
