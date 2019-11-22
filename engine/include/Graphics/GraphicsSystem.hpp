//
//
//

#ifndef AEYON3D_RENDERER_HPP
#define AEYON3D_RENDERER_HPP

#include "ECS/System.hpp"
#include "glad/glad.h"
#include "Graphics/Texture.hpp"
#include "ECS/Entity.hpp"
#include "Resource.hpp"
#include "Graphics/Frustum.hpp"
#include "Time.hpp"

namespace aeyon
{
	class Camera;
	class Mesh;
	class Light;
	class Material;
	class Transform;
	class SDLWindow;

	class GraphicsSystem : public System
	{
	public:
		struct Batch
		{
			Resource<Material> material;
			std::vector<GLuint> vaos;
			std::vector<GLuint> ebos;
			std::vector<Component<Transform>> transforms;
			std::vector<GLsizei> numTriangles;
			std::vector<GLint> offsets;
		};

		struct CameraInfo
		{
			Component<Transform> transform;
			Component<Camera> camera;
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
		Entity m_skyBox;

		std::vector<Entity> m_lights;
		std::vector<CameraInfo> m_cameras;
		std::unordered_map<Material*, Batch> m_batches;
		std::vector<Entity> m_scene;

		Resource<Texture> m_shadowMap;
		GLuint m_shadowFBO;

		float m_previousTime;
		float m_frameTime = 0.0f;
		int m_numFrames = 0;


		void generateRenderInfo(const std::string& shaderName);
		void setCommonShaderProperties();
		void renderVAOs(std::uint32_t passIndex);
		void bindMaterial(Resource<Material>& material);


	public:
		explicit GraphicsSystem(SDLWindow* window);
		~GraphicsSystem() override;

		void setSkybox(Entity skybox);

		SDLWindow* getWindow();

		void setup() override;
		void update() override;

		void render();
	};
}


#endif //AEYON3D_RENDERER_HPP
