//
//
//

#include "Graphics/GraphicsSystem.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "glad/glad.h"
#include "Event/QuitEvent.hpp"
#include "Window.hpp"
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


namespace aeyon
{
	GraphicsSystem::GraphicsSystem(Window* window):  m_window(window),
	m_shadowMap(std::make_shared<ResourceData<Texture>>("ShadowMap", std::make_unique<Texture>(Texture::Type::Tex2D, PixelFormat::Depth, ShadowTexWidth, ShadowTexHeight))),
	m_shadowFBO(0)
	{
		requireComponent<Transform>();
		acceptComponent<MeshRenderer>();
		acceptComponent<Light>();
		acceptComponent<Camera>();

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
				m_shadowMap->getGLHandle(),
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

	void GraphicsSystem::init()
	{
		m_world->eventSystem.subscribe<QuitEvent>([&](const QuitEvent& event) {
			m_window->close();
		});
	}

	void GraphicsSystem::update()
	{
		// TODO: Setup temporary scene till I have implemented the world's scene graph
		Scene scene;
		for (const auto& entity : getEntities())
		{
			scene.addEntity(entity);
		}

		render(scene);
	}

	void GraphicsSystem::render(Scene& scene)
	{
		m_scene = scene;
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

		glCullFace(GL_FRONT);

		renderVAOs(1);

		glCullFace(GL_BACK);

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

			auto skyBoxMesh = m_skyBox.getComponent<MeshRenderer>()->getSharedMesh();

			Batch& b = m_batches[skyBoxMesh->getSharedMaterial().get()];

			b.material = skyBoxMesh->getSharedMaterial();
			b.vaos.push_back(*static_cast<GLuint*>(skyBoxMesh->getVertexBuffer()->getNativeHandle()));
			b.ebos.push_back(*static_cast<GLuint*>(skyBoxMesh->getIndexBuffer()->getNativeHandle()));
			b.transforms.push_back(m_skyBox.getComponent<Transform>());
			b.numTriangles.push_back(skyBoxMesh->getTriangles().size());

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
		for (auto& entity : m_scene.getEntities())
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

		for (auto& entity : m_scene.getEntities())
		{
			if (entity.hasComponent<MeshRenderer>())
			{
				auto mesh = entity.getComponent<MeshRenderer>()->getSharedMesh();

				//Frustum culling
				//TODO: Implement OBB test
				//TODO: Adjust culling for shadow casters
				const Bounds& bb = mesh->getBoundingBox();

				const auto& toWorld = entity.getComponent<Transform>()->getLocalToWorldMatrix();

				std::vector<glm::vec3> vs = {
						glm::vec3(toWorld * glm::vec4(bb.getMin(), 1.0f)),
						glm::vec3(toWorld * glm::vec4(bb.getMin() + glm::vec3(bb.getSize().x, 0.0f, 0.0f), 1.0f)),
						glm::vec3(toWorld * glm::vec4(bb.getMin() + glm::vec3(0.0f, bb.getSize().y, 0.0f), 1.0f)),
						glm::vec3(toWorld * glm::vec4(bb.getMin() + glm::vec3(0.0f, 0.0f, bb.getSize().z), 1.0f)),
						glm::vec3(toWorld * glm::vec4(bb.getMax(), 1.0f)),
						glm::vec3(toWorld * glm::vec4(bb.getMax() - glm::vec3(bb.getSize().x, 0.0f, 0.0f), 1.0f)),
						glm::vec3(toWorld * glm::vec4(bb.getMax() - glm::vec3(0.0f, bb.getSize().y, 0.0f), 1.0f)),
						glm::vec3(toWorld * glm::vec4(bb.getMax() - glm::vec3(0.0f, 0.0f, bb.getSize().z), 1.0f))
				};

				if (!m_cameras[0].frustum.testBox(vs))
				{
					continue;
				}

				auto material = mesh->getSharedMaterial();

				if (mesh->needsUpdate())
					mesh->apply();

				if (material->getShader()->getName() != shaderName)
					continue;

				Batch& batch = m_batches[material.get()];
				batch.material = material;

				batch.vaos.push_back(*static_cast<GLuint*>(mesh->getVertexBuffer()->getNativeHandle()));
				batch.ebos.push_back(*static_cast<GLuint*>(mesh->getIndexBuffer()->getNativeHandle()));
				batch.transforms.push_back(entity.getComponent<Transform>());
				batch.numTriangles.push_back(mesh->getTriangles().size());
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

		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.5f, 7.5f);

		glm::mat4 lightView = glm::lookAt(
				glm::vec3(-1.0f, 2.0f, -3.0f),
				glm::vec3(0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f)
		);

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
				batch.first->setParameter("_M", transform->getLocalToWorldMatrix());
				batch.first->setParameter("_M_Inv", transform->getWorldToLocalMatrix());
				batch.first->setParameter("_MVP", mainCamera.projectionMatrix * mainCamera.viewMatrix * transform->getLocalToWorldMatrix());
				batch.first->setParameter("_MV_T_Inv", glm::transpose(glm::inverse(mainCamera.viewMatrix * transform->getLocalToWorldMatrix())));

				bindMaterial(batch.second.material);

				glBindVertexArray(batch.second.vaos[i]);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch.second.ebos[i]);
				glDrawElements(GL_TRIANGLES, batch.second.numTriangles[i], GL_UNSIGNED_INT, reinterpret_cast<void*>(0));
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
				glBindTexture(static_cast<GLenum>(tex->getType()), tex->getGLHandle());
				glUniform1i(p.second.shaderProperty.location, tidx);
			}
			else
			{
				std::visit(PropertyVisitor(p.second.shaderProperty.location), p.second.value);
			}
		}
	}

	void GraphicsSystem::setSkybox(EntityHandle skybox)
	{
		m_skyBox = std::move(skybox);
	}
}
