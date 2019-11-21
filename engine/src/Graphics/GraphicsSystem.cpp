//
//
//

#include "Graphics/GraphicsSystem.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "glad/glad.h"
#include "Event/QuitEvent.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/MeshRenderer.hpp"
#include "Graphics/Light.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Scene.hpp"
#include "Primitive.hpp"
#include "Graphics/PropertyVisitor.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <iostream>
#include "SDLWindow.hpp"



namespace aeyon
{
	void APIENTRY glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
																const GLchar* message, const void* userParam)
	{
		if (type == GL_DEBUG_TYPE_ERROR_ARB)
			throw std::runtime_error(message);
	}

	GraphicsSystem::GraphicsSystem(SDLWindow* window)
	: m_window(window), m_shadowFBO(0)
	{
		requireComponent<Transform>();
		acceptComponent<MeshRenderer>();
		acceptComponent<Light>();
		acceptComponent<Camera>();

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




		// Load shadow map texture target and buffers

		m_shadowMap = Resource<Texture>(std::make_shared<ResourceData<Texture>>("ShadowMap", std::make_unique<Texture>(Texture::Type::Tex2D, PixelFormat::Depth, ShadowTexWidth, ShadowTexHeight)));

		glGenFramebuffers(1, &m_shadowFBO);

		m_shadowMap->setAnisoLevel(1.0f);
		m_shadowMap->setFilterMode(Texture::FilterMode::Point);
		m_shadowMap->setWrapMode(Texture::WrapMode::ClampToBorder);
		m_shadowMap->setBorderColor(Color::White);

		m_shadowMap->apply();

		glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
		glFramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_DEPTH_ATTACHMENT,
				GL_TEXTURE_2D,
				m_shadowMap->getNativeHandle(),
				0
		);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			throw std::runtime_error("Error: The framebuffer is not complete!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		glViewport(0, 0, window->getViewportWidth(), window->getViewportHeight());
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	}

	GraphicsSystem::~GraphicsSystem()
	{
		if (m_shadowFBO)
			glDeleteFramebuffers(1, &m_shadowFBO);
	}

	void GraphicsSystem::start()
	{
		m_world->eventSystem.subscribe<QuitEvent>([&](const QuitEvent& event) {
			m_window->close();
		});
	}

	void GraphicsSystem::update()
	{
		// TODO: Setup temporary scene till I have implemented the world's scene graph
		m_scene.clear();
		for (const auto& entity : getEntities())
		{
			m_scene.push_back(entity);
		}

		render();
	}

	void GraphicsSystem::render()
	{
		m_cameras.clear();
		m_lights.clear();
		m_batches.clear();

		generateRenderInfo("Standard");

		if (m_cameras.empty())
		{
			throw std::runtime_error("Warning: No main camera defined!");
			return;
		}

		setCommonShaderProperties();

		for (auto& batch : m_batches)
		{
			batch.first->setParameter("shadow_map", m_shadowMap);
		}

		// Render Shadow Map (TODO: Check if shadows are enabled. Set shadow variables)

		glViewport(0, 0, ShadowTexWidth, ShadowTexHeight);

		glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		//glCullFace(GL_FRONT);

		renderVAOs(1);

		//glCullFace(GL_BACK);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0, 0, m_window->getViewportWidth(), m_window->getViewportHeight());


		// Render World

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// TODO: The dirty flag within the bindMaterial method messes the whole thing up completely. I've temporarily
		//       disabled the dirty checks.

		glEnable(GL_FRAMEBUFFER_SRGB);

		renderVAOs(0);


		// Render Skybox

		if (m_skyBox)
		{
			m_batches.clear();

			auto skyBoxMesh = m_skyBox.getComponent<MeshRenderer>();

			Batch& b = m_batches[skyBoxMesh->getMaterial().get()];

			b.material = skyBoxMesh->getMaterial();
			b.vaos.push_back(*static_cast<GLuint*>(skyBoxMesh->getMesh()->getVertexBuffer().getNativeHandle()));
			b.ebos.push_back(*static_cast<GLuint*>(skyBoxMesh->getMesh()->getIndexBuffer().getNativeHandle()));
			b.transforms.push_back(m_skyBox.getComponent<Transform>());
			b.numTriangles.push_back(skyBoxMesh->getMesh()->getTriangles().size());
			b.offsets.push_back(0);

			setCommonShaderProperties();

			glCullFace(GL_FRONT);
			glDepthFunc(GL_LEQUAL);

			renderVAOs(0);

			glDepthFunc(GL_LESS);
			glCullFace(GL_BACK);
		}

		glDisable(GL_FRAMEBUFFER_SRGB);

	}

	void GraphicsSystem::generateRenderInfo(const std::string& shaderName)
	{
		for (auto& entity : m_scene)
		{
			if (entity.hasComponent<Camera>())
			{
				CameraInfo info;
				info.transform = entity.getComponent<Transform>();
				info.camera = entity.getComponent<Camera>();

				info.frustum = Frustum(info.transform->getPosition(), info.transform->getForward(), info.transform->getUp(),
															 info.camera->getNearClipPlane(), info.camera->getFarClipPlane(), info.camera->getFieldOfView(),
															 static_cast<float>(m_window->getViewportWidth()) / static_cast<float>(m_window->getViewportHeight()));

				info.viewMatrix = glm::lookAtLH(
						info.transform->getPosition(),
						info.transform->getPosition() + info.transform->getForward(),
						info.transform->getUp()
				);

				info.viewMatrixInverse = glm::inverse(info.viewMatrix);

				info.projectionMatrix = glm::perspective(
						glm::radians(info.camera->getFieldOfView()),
						static_cast<float>(m_window->getViewportWidth()) / static_cast<float>(m_window->getViewportHeight()),
						info.camera->getNearClipPlane(), info.camera->getFarClipPlane()
				);

				// Transform engine clip space to OpenGL clip space
				info.projectionMatrix = info.projectionMatrix * glm::scale(glm::mat4(1.0), glm::vec3(1.0, 1.0, -1.0));

				info.projectionMatrixInverse = glm::inverse(info.projectionMatrix);

				m_cameras.push_back(info);
			}
		}

		for (auto& entity : m_scene)
		{
			if (entity.hasComponent<MeshRenderer>())
			{
				auto mesh = entity.getComponent<MeshRenderer>();

				//Frustum culling
				//TODO: Adjust culling for shadow casters
				Bounds bb = mesh->getMesh()->getBounds();

				const auto& toWorld = entity.getComponent<Transform>()->getLocalToWorldMatrix();

				auto vs = bb.getVertices();

				for (auto& v : vs)
				{
					v = toWorld * glm::vec4(v, 1.0f);
				}

				if (!m_cameras[0].frustum.intersects(vs))
				{
					//continue;
				}

				for (std::size_t i = 0; i < mesh->getMesh()->getSubMeshCount(); i++)
				{
					auto material = mesh->getMaterials().at(i);

					if (material->getShader()->getName() != shaderName)
						continue;

					Batch& batch = m_batches[material.get()];
					batch.material = material;

					batch.vaos.push_back(*static_cast<GLuint*>(mesh->getMesh()->getVertexBuffer().getNativeHandle()));
					batch.ebos.push_back(*static_cast<GLuint*>(mesh->getMesh()->getIndexBuffer().getNativeHandle()));
					batch.transforms.push_back(entity.getComponent<Transform>());
					batch.numTriangles.push_back(mesh->getMesh()->getTriangles(i).size());
					batch.offsets.push_back(mesh->getMesh()->getSubMeshOffset(i));
				}
			}

			if (entity.hasComponent<Light>())
			{
				m_lights.push_back(entity);
			}
		}
	}

	void GraphicsSystem::setCommonShaderProperties()
	{
		std::vector<glm::vec4> lightPositions(8, glm::vec4(0.0f));
		std::vector<glm::vec4> lightColors(8, glm::vec4(0.0f));
		std::vector<glm::vec4> attenuations(8, glm::vec4(0.0f));
		std::vector<glm::mat4> worldToLightMatrices(8, glm::mat4(1.0f));
		std::vector<glm::mat4> lightToWorldMatrices(8, glm::mat4(1.0f));

		glm::vec4 attenuation(1.0f, 0.09f, 0.032f, 0.0f);

		const CameraInfo& mainCamera = m_cameras.front();

		for (std::size_t i = 0; i < m_lights.size(); i++)
		{
			Light* l = m_lights[i].getComponent<Light>().get();
			Transform* lightTransform = m_lights[i].getComponent<Transform>().get();
			glm::vec4 pos;

			// Transform either the light direction (for directional lights) or the light position (point lights) into view space
			if (l->getType() == Light::Type::Directional)
			{
				pos = glm::vec4(glm::mat3(mainCamera.viewMatrix) * lightTransform->getForward(), 0.0f);
				attenuation.w = -1.0f;
			}
			else
			{
				pos = mainCamera.viewMatrix * glm::vec4(lightTransform->getPosition(), 1.0f);
				attenuation.w = 1.0f;
			}

			lightPositions[i] = pos;
			lightColors[i] = glm::vec4(glm::vec3(l->getColor()) * l->getIntensity(), 1.0f);
			attenuations[i] = attenuation;

			// TODO: Fill light matrices list...

		}

		// TODO: This currently only works with ONE light. I first need to check if my matrix array implementation is
		//       correct before creating a proper light matrix array.

		Bounds sceneBounds;
		for (auto& entity : m_scene)
		{
			if (entity.hasComponent<MeshRenderer>())
			{
				Bounds objBounds = entity.getComponent<MeshRenderer>()->getMesh()->getBounds();

				// Omit plane
				if (entity.getComponent<Transform>()->getScale().x > 5.0f)
					continue;

				auto vs = objBounds.getVertices();

				for (auto& v : vs)
				{
					v = entity.getComponent<Transform>()->getLocalToWorldMatrix() * glm::vec4(v, 1.0f);
					sceneBounds.encompass(v);
				}
			}
		}

		glm::mat4 lightView = glm::lookAtLH(
				sceneBounds.getCenter(),
				sceneBounds.getCenter() + m_lights[0].getComponent<Transform>()->getForward(),
				glm::vec3(0.0f, 1.0f, 0.0f)
		);


		Bounds lightBounds;
		for (auto& v : sceneBounds.getVertices())
		{
			lightBounds.encompass(lightView * glm::vec4(v, 1.0f));
		}

		//glm::mat4 lightProjection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.5f, 7.5f);

		lightBounds.expand(glm::vec3(5.0f));

		glm::mat4 lightProjection = glm::ortho(
				-lightBounds.getExtents().x,
				lightBounds.getExtents().x,
				-lightBounds.getExtents().y,
				lightBounds.getExtents().y,
				lightBounds.getExtents().z,
				-lightBounds.getExtents().z
		);
//
//		std::cout << "{" << sceneBounds.getMin().x << ", " << sceneBounds.getMin().y << ", " << sceneBounds.getMin().z << "}\n";
//		std::cout << "{" << sceneBounds.getMax().x << ", " << sceneBounds.getMax().y << ", " << sceneBounds.getMax().z << "}\n" << std::endl;

		glm::mat4 lightSpaceMatrix = lightProjection * lightView;

		for (auto& batch : m_batches)
		{
			batch.first->setParameter("_V", mainCamera.viewMatrix);
			batch.first->setParameter("_P", mainCamera.projectionMatrix);
			batch.first->setParameter("_VP", mainCamera.projectionMatrix * mainCamera.viewMatrix);
			batch.first->setParameter("_AmbientColor", glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			batch.first->setParameter("_LightPosition", lightPositions);
			batch.first->setParameter("_LightColor", lightColors);
			batch.first->setParameter("_AttenuationFactors", attenuations);
			batch.first->setParameter("_TextureOffset", batch.first->getTextureOffset());
			batch.first->setParameter("_TextureScale", batch.first->getTextureScale());

			batch.first->setParameter("_WorldToLight", lightSpaceMatrix);
			batch.first->setParameter("_LightToWorld", glm::inverse(lightSpaceMatrix));
		}
	}

	void GraphicsSystem::renderVAOs(std::uint32_t passIndex)
	{
		for (auto& batch : m_batches)
		{
			ShaderProgram& program = batch.first->getShader()->getShaderProgram(passIndex);
			const CameraInfo& mainCamera = m_cameras.front();

			glUseProgram(program.get());

			for (std::size_t i = 0; i < batch.second.vaos.size(); i++)
			{
				auto transform = batch.second.transforms[i];
				auto parent = transform->getParent();

				// TODO: This should go into the transform class...
				// ALSO: Reactivate frustum culling
				glm::mat4 M = transform->getLocalToWorldMatrix();

				if (parent)
				{
					M = M * parent->getLocalToWorldMatrix();
				}

				batch.first->setParameter("_M", M);
				batch.first->setParameter("_M_Inv", glm::inverse(M));
				batch.first->setParameter("_MVP", mainCamera.projectionMatrix * mainCamera.viewMatrix * M);
				batch.first->setParameter("_MV_Inv_T", glm::transpose(glm::inverse(mainCamera.viewMatrix * M)));

				bindMaterial(batch.second.material);

				glBindVertexArray(batch.second.vaos[i]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.second.ebos[i]);
				glDrawElementsBaseVertex(GL_TRIANGLES, batch.second.numTriangles[i], GL_UNSIGNED_INT, reinterpret_cast<void*>(0), batch.second.offsets[i]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
				glBindVertexArray(0);

				for (auto& t : batch.first->getTextureIndexMap())
				{
					glActiveTexture(GL_TEXTURE0 + t.second);
					glBindTexture(GL_TEXTURE_2D, 0);
					glBindTexture(GL_TEXTURE_3D, 0);
					glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
				}
			}
			glUseProgram(0);
		}
	}

	void GraphicsSystem::bindMaterial(Resource<Material>& material)
	{
		for (auto& p : material->getParameterMap())
		{
			if (std::holds_alternative<Resource<Texture>>(p.second.value))
			{
				auto tex = std::get<Resource<Texture>>(p.second.value);
				GLuint tidx = material->getTextureIndexMap().at(p.first);
				glActiveTexture(GL_TEXTURE0 + tidx);
				glBindTexture(static_cast<GLenum>(tex->getType()), tex->getNativeHandle());
				glUniform1i(p.second.shaderProperty.location, tidx);
			}
			else
			{
				std::visit(PropertyVisitor(p.second.shaderProperty.location), p.second.value);
			}
		}
	}

	void GraphicsSystem::setSkybox(Entity skybox)
	{
		m_skyBox = std::move(skybox);
	}

	SDLWindow* GraphicsSystem::getWindow()
	{
		return m_window;
	}
}
