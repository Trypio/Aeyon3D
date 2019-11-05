//
//
//

#ifndef AEYON3D_ENGINE_HPP
#define AEYON3D_ENGINE_HPP
#include "ECS/World.hpp"
#include "Window.hpp"
#include "Input/Input.hpp"
#include "ResourceCache.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/GraphicsSystem.hpp"
#include "Audio/AudioClip.hpp"
#include <memory>
#include "TextureCache.hpp"
#include "ShaderCache.hpp"

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
	};
}


#endif //AEYON3D_ENGINE_HPP
