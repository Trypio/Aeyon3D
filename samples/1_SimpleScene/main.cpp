
#include "Engine.hpp"
#include "Util.hpp"
#include "Primitive.hpp"
#include "Graphics/Light.hpp"
#include "FirstPersonController.hpp"
#include "Time.hpp"
#include "Graphics/Material.hpp"

using namespace aeyon;

class SimpleScene : public Engine
{
private:
	ComponentHandle<Transform> cubeTransform1;
	ComponentHandle<Transform> cubeTransform2;

public:
	void start() override
	{
		Resource<Texture> stoneDiffuse = m_textureCache.load("Bricks18_col", {Texture::Type::Tex2D, {"assets/textures/Bricks18_col.jpg"}, PixelFormat::sRGB8, true});
		Resource<Texture> stoneGloss = m_textureCache.load("Bricks18_rgh", {Texture::Type::Tex2D, {"assets/textures/Bricks18_rgh.jpg"}, PixelFormat::R8, true});
		Resource<Texture> stoneNormals = m_textureCache.load("Bricks18_nrm", {Texture::Type::Tex2D, {"assets/textures/Bricks18_nrm.jpg"}, PixelFormat::RGB8, true});
		Resource<Texture> groundDiffuse = m_textureCache.load("Ground03_col", {Texture::Type::Tex2D, {"assets/textures/Ground03_col.jpg"}, PixelFormat::sRGB8, true});
		Resource<Texture> groundGloss = m_textureCache.load("Ground03_rgh", {Texture::Type::Tex2D, {"assets/textures/Ground03_rgh.jpg"}, PixelFormat::R8, true});
		Resource<Texture> groundNormals = m_textureCache.load("Ground03_nrm", {Texture::Type::Tex2D, {"assets/textures/Ground03_nrm.jpg"}, PixelFormat::RGB8, true});
		Resource<Texture> skyboxCubemap = m_textureCache.load("skybox", {
				Texture::Type::Cube,
				{
						"assets/textures/right.jpg",
						"assets/textures/left.jpg",
						"assets/textures/top.jpg",
						"assets/textures/bottom.jpg",
						"assets/textures/front.jpg",
						"assets/textures/back.jpg"
				}, PixelFormat::sRGB8, true});

		Resource<Shader> standardShader = m_shaderCache.load("Standard", {"assets/shaders/Standard.shader"});
		Resource<Shader> skyboxShader = m_shaderCache.load("Skybox", {"assets/shaders/Skybox.shader"});

		Resource<Material> cubeMaterial(std::make_shared<ResourceData<Material>>("CubeMaterial", std::make_unique<Material>(standardShader)));
		cubeMaterial->setParameter("diffuse_texture", stoneDiffuse);
		cubeMaterial->setParameter("specular_texture", stoneGloss);
		cubeMaterial->setParameter("normal_texture", stoneNormals);
		// TODO: Implement default shader values
		cubeMaterial->setParameter("diffuse_color", glm::vec4(1.0f));
		cubeMaterial->setParameter("specular_color", glm::vec4(0.2f));
		cubeMaterial->setParameter("shininess", 8.0f);
		cubeMaterial->setTextureScale(glm::vec2(1.0f));

		Resource<Material> groundMaterial(std::make_shared<ResourceData<Material>>("GroundMaterial", std::make_unique<Material>(standardShader)));
		groundMaterial->setParameter("diffuse_texture", groundDiffuse);
		groundMaterial->setParameter("specular_texture", groundGloss);
		groundMaterial->setParameter("normal_texture", groundNormals);
		groundMaterial->setParameter("diffuse_color", glm::vec4(1.0f));
		groundMaterial->setParameter("specular_color", glm::vec4(0.2f));
		groundMaterial->setParameter("shininess", 64.0f);

		Resource<Material> skyBoxMaterial(std::make_shared<ResourceData<Material>>("SkyboxMaterial", std::make_unique<Material>(skyboxShader)));
		skyBoxMaterial->setParameter("skybox", skyboxCubemap);

		auto skyboxEntity = Primitive::createCube(m_world.get(), false, false);
		skyboxEntity.removeComponent<BoxCollider>();
		auto skyBoxMesh = skyboxEntity.getComponent<MeshRenderer>()->getSharedMesh();
		auto positions = skyBoxMesh->getPositions();
		std::for_each(positions.begin(), positions.end(), [](glm::vec3& v) { v *= 2.0f; });
		skyBoxMesh->setPositions(std::move(positions));
		skyBoxMesh->setSharedMaterial(skyBoxMaterial);
		skyBoxMesh->apply();

		m_graphics->setSkybox(skyboxEntity);

		auto cube1 = Primitive::createCube(m_world.get());
		cubeTransform1 = cube1.getComponent<Transform>();
		cubeTransform1->setPosition({0.5f, 0.5f, 0.5f});
		auto cubeMesh1 = cube1.getComponent<MeshRenderer>()->getSharedMesh();
		cubeMesh1->setSharedMaterial(cubeMaterial);

		auto cube2 = Primitive::createCube(m_world.get());
		cubeTransform2 = cube2.getComponent<Transform>();
		cubeTransform2->setPosition({2.0f, 0.5f, 0.0f});
		auto cubeMesh2 = cube2.getComponent<MeshRenderer>()->getSharedMesh();
		cubeMesh2->setSharedMaterial(cubeMaterial);



		auto ground = Primitive::createPlane(m_world.get());
		auto groundTransform = ground.getComponent<Transform>();
		groundTransform->setScale({50.0f, 0.1f, 50.0f});
		auto groundMesh = ground.getComponent<MeshRenderer>()->getSharedMesh();
		groundMaterial->setTextureScale({50.0f, 50.0f});
		groundMesh->setSharedMaterial(groundMaterial);

		auto directionalLight = m_world->createEntity();
		auto directionalLightTransform = directionalLight.addComponent<Transform>();
		auto directionalLightLight = directionalLight.addComponent<Light>();
		directionalLightLight->setColor(Color::fromRGBA32(255, 255, 225, 255));
		directionalLightLight->setIntensity(1.2f);
		directionalLightTransform->rotate({45.0f, 35.0f, 0.0f});

		auto camera = m_world->createEntity();
		auto cameraTransform = camera.addComponent<Transform>();
		camera.addComponent<Camera>();
		auto controller = camera.addComponent<FirstPersonController>();
		controller->m_moveSpeed = 0.003f;
		controller->m_mouseSensitivity = 0.1f;

		cameraTransform->translate({0.0f, 0.5f, -2.0f});
	}

	void update() override
	{
		if (m_input->isKeyDown(KeyCode::Escape))
		{
			m_window->close();
		}


		if (m_input->isKeyDown(KeyCode::Keypad4))
		{
			cubeTransform1->translate({-0.001f * Time::getDeltaTime(), 0.0f, 0.0f});
		}

		if (m_input->isKeyDown(KeyCode::Keypad6))
		{
			cubeTransform1->translate({0.001f * Time::getDeltaTime(), 0.0f, 0.0f});
		}

		if (m_input->isKeyDown(KeyCode::Keypad8))
		{
			cubeTransform1->translate({0.0f, 0.0f, 0.001f * Time::getDeltaTime()});
		}

		if (m_input->isKeyDown(KeyCode::Keypad2))
		{
			cubeTransform1->translate({0.0f, 0.0f, -0.001f * Time::getDeltaTime()});
		}

		if (m_input->isKeyDown(KeyCode::Keypad7))
		{
			cubeTransform1->rotate({0.0f, -0.1f * Time::getDeltaTime(), 0.0f});
		}

		if (m_input->isKeyDown(KeyCode::Keypad9))
		{
			cubeTransform1->rotate({0.0f, 0.1f * Time::getDeltaTime(), 0.0f});
		}

		if (m_input->isKeyDown(KeyCode::KeypadMinus))
		{
			cubeTransform1->rotate({0.1f * Time::getDeltaTime(), 0.0f, 0.0f});
		}

		if (m_input->isKeyDown(KeyCode::KeypadPlus))
		{
			cubeTransform1->rotate({-0.1f * Time::getDeltaTime(), 0.0f, 0.0f});
		}

		if (m_input->isKeyDown(KeyCode::Keypad1))
		{
			cubeTransform1->rotate({0.0f, 0.0f, 0.1f * Time::getDeltaTime()});
		}

		if (m_input->isKeyDown(KeyCode::Keypad3))
		{
			cubeTransform1->rotate({0.0f, 0.0f, -0.1f * Time::getDeltaTime()});
		}
	}
};

int main(int argc, char* argv[])
{
	SimpleScene app;
	app.run();

	return 0;
}