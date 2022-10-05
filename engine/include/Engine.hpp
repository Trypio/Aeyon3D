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
#include "Input/SDLInput.hpp"
#include "System.hpp"
#include "SceneLoader.hpp"

class aiNode;
class aiScene;

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

		std::vector<std::unique_ptr<System>> userSystems;

		TextureCache textureCache;
		ShaderCache shaderCache;
        SceneLoader sceneLoader;

		virtual void setup();
		virtual void start();
		virtual void update();
		virtual void fixedUpdate();
		virtual void lateUpdate();

		std::vector<Actor> loadModel(const std::string& path, Resource<Material> material);
		void processNode(const aiScene* scene, const aiNode* node, Actor root, std::vector<Actor>& children,  Resource<Material> material);

	public:
		Engine() = default;
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		virtual ~Engine() = default;

		void run();
	};
}


#endif //AEYON3D_ENGINE_HPP
