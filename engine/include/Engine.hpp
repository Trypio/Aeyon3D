//
//
//

#ifndef AEYON3D_ENGINE_HPP
#define AEYON3D_ENGINE_HPP

#include <memory>
#include "TextureCache.hpp"
#include "ShaderCache.hpp"
#include "ECS/Entity.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/GraphicsSystem.hpp"
#include "Input/Input.hpp"
#include "Window.hpp"
#include "ECS/World.hpp"
#include "Event/EventSystem.hpp"

class aiNode;
class aiScene;

namespace aeyon
{
	class Engine
	{
	protected:
		EventSystem eventSystem;

		std::unique_ptr<World> world;
		std::unique_ptr<Window> window;
		std::unique_ptr<Input> input;
		GraphicsSystem* graphics = nullptr;

		TextureCache textureCache;
		ShaderCache shaderCache;

		virtual void setup();
		virtual void start();
		virtual void update();
		virtual void fixedUpdate();
		virtual void lateUpdate();

		Entity loadModel(const std::string& path, Resource<Material> material);
		void processNode(const aiScene* scene, const aiNode* node, Entity entity, Resource<Material> material);

	public:
		Engine() = default;
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		virtual ~Engine() = default;

		void run();
	};
}


#endif //AEYON3D_ENGINE_HPP
