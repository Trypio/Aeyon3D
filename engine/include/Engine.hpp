//
//
//

#ifndef AEYON3D_ENGINE_HPP
#define AEYON3D_ENGINE_HPP

#include <memory>
#include "TextureCache.hpp"
#include "ShaderCache.hpp"
#include "Graphics/Material.hpp"
#include "Event/EventSystem.hpp"
#include "Scene.hpp"
#include "Graphics/SDLWindow.hpp"
#include "GUI/GUISystem.hpp"
#include "Graphics/GraphicsSystem.hpp"
#include "BehaviorSystem.hpp"
#include "Input/SDLInput.hpp"
#include "System.hpp"
#include "SceneLoader.hpp"

namespace aeyon
{
	class Engine
	{
	protected:
		EventSystem m_eventSystem;

		std::unique_ptr<Window> window;
		std::unique_ptr<Input> input;
		std::unique_ptr<GraphicsSystem> graphics;
		std::unique_ptr<GUISystem> gui;
        std::unique_ptr<BehaviorSystem> behaviors;

		TextureCache textureCache;
		ShaderCache shaderCache;
        SceneLoader sceneLoader;

		virtual void setup();
		virtual void start();
		virtual void update();
		virtual void fixedUpdate();
		virtual void lateUpdate();

	public:
		Engine() = default;
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		virtual ~Engine() = default;

		void run();
	};
}


#endif //AEYON3D_ENGINE_HPP
