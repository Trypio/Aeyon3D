//
//
//

#ifndef AEYON3D_RENDERER_HPP
#define AEYON3D_RENDERER_HPP

#include "glad/glad.h"
#include "Graphics/Texture.hpp"
#include "Resource.hpp"
#include "Graphics/Frustum.hpp"
#include "Time.hpp"
#include "System.hpp"

#include <unordered_map>

namespace aeyon
{
	class Camera;
	class Mesh;
	class Light;
	class Material;
	class Transform;
	class SDLWindow;
	class Scene;
	class Actor;

	class GraphicsSystem : public System
	{
	public:
		struct Batch
		{
			Resource<Material> material;
			std::vector<GLuint> vaos;
			std::vector<GLuint> ebos;
			std::vector<Transform*> transforms;
			std::vector<GLsizei> numTriangles;
			std::vector<GLint> offsets;
		};

		struct CameraInfo
		{
			Transform* transform;
			Camera* camera;
			Frustum frustum;
			glm::mat4 viewMatrix = glm::mat4(1.0f);
			glm::mat4 viewMatrixInverse = glm::mat4(1.0f);
			glm::mat4 projectionMatrix = glm::mat4(1.0f);
			glm::mat4 projectionMatrixInverse = glm::mat4(1.0f);
		};

	private:
		const int ShadowTexWidth = 2048;
		const int ShadowTexHeight = 2048;

		SDLWindow* m_window;
		Actor* m_skyBox;

		std::vector<Actor*> m_lights;
		std::vector<CameraInfo> m_cameras;
		std::unordered_map<Material*, Batch> m_batches;
		Scene* m_scene;

		Resource<Texture> m_shadowMap;
		GLuint m_shadowFBO;


		void generateRenderInfo(const std::string& shaderName);
		void setCommonShaderProperties();
		void renderVAOs(std::uint32_t passIndex);
		void bindMaterial(Resource<Material>& material);


	public:
		explicit GraphicsSystem(Scene* scene, SDLWindow* window);
		~GraphicsSystem() override;

		void setSkybox(Actor* skybox);

		SDLWindow* getWindow();

		void setup() override;
		void update() override;

		void render();
	};
}


#endif //AEYON3D_RENDERER_HPP
