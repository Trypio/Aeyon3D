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

class aiNode;
class aiScene;

namespace aeyon
{
	class Engine
	{
	protected:
		std::unique_ptr<World> m_world;
		std::unique_ptr<Window> m_window;
		std::unique_ptr<Input> m_input;
		GraphicsSystem* m_graphics = nullptr;

		TextureCache m_textureCache;
		ShaderCache m_shaderCache;

	public:
		Engine() = default;
		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		virtual ~Engine() = default;

		virtual void setup();
		virtual void start();
		virtual void update();
		virtual void fixedUpdate();
		virtual void lateUpdate();

		void run();
		Entity loadModel(const std::string& path, Resource<Material> material);
		void processNode(const aiScene* scene, const aiNode* node, Entity entity, Resource<Material> material);
	};
}


#endif //AEYON3D_ENGINE_HPP
