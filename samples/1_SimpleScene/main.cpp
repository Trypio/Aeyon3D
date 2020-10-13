
#include "Engine.hpp"
#include "Graphics/GraphicsSystem.hpp"
#include "Util.hpp"
#include "Primitive.hpp"
#include "Graphics/Light.hpp"
#include "FirstPersonController.hpp"
#include "Time.hpp"
#include "Graphics/Material.hpp"
#include "Input/Input.hpp"
#include "Window.hpp"
#include "Transform.hpp"

using namespace aeyon;

class SimpleScene : public Engine
{
private:
	Transform* cubeTransform1;
	Transform* cubeTransform2;

public:
	void start() override
	{
		Resource<Texture> stoneDiffuse = textureCache.load("Bricks18_col", {Texture::Type::Tex2D, {"assets/textures/Bricks18_col.jpg"}, PixelFormat::sRGB8, true});
		Resource<Texture> stoneGloss = textureCache.load("Bricks18_rgh", {Texture::Type::Tex2D, {"assets/textures/Bricks18_rgh.jpg"}, PixelFormat::R8, true});
		Resource<Texture> stoneNormals = textureCache.load("Bricks18_nrm", {Texture::Type::Tex2D, {"assets/textures/Bricks18_nrm.jpg"}, PixelFormat::RGB8, true});
		Resource<Texture> groundDiffuse = textureCache.load("Ground03_col", {Texture::Type::Tex2D, {"assets/textures/Ground03_col.jpg"}, PixelFormat::sRGB8, true});
		Resource<Texture> groundGloss = textureCache.load("Ground03_rgh", {Texture::Type::Tex2D, {"assets/textures/Ground03_rgh.jpg"}, PixelFormat::R8, true});
		Resource<Texture> groundNormals = textureCache.load("Ground03_nrm", {Texture::Type::Tex2D, {"assets/textures/Ground03_nrm.jpg"}, PixelFormat::RGB8, true});
		Resource<Texture> skyboxCubemap = textureCache.load("skybox", {
				Texture::Type::Cube,
				{
						"assets/textures/right.jpg",
						"assets/textures/left.jpg",
						"assets/textures/top.jpg",
						"assets/textures/bottom.jpg",
						"assets/textures/front.jpg",
						"assets/textures/back.jpg"
				}, PixelFormat::sRGB8, true});

		Resource<Shader> standardShader = shaderCache.load("Standard", {"assets/shaders/Standard.shader"});
		Resource<Shader> skyboxShader = shaderCache.load("Skybox", {"assets/shaders/Skybox.shader"});

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

		auto skyboxActor = Primitive::createCube(false, false);
		skyboxActor->removeComponent<BoxCollider>();
		auto skyBoxMesh = skyboxActor->getComponent<MeshRenderer>();
		auto positions = skyBoxMesh->getMesh()->getPositions();
		std::for_each(positions.begin(), positions.end(), [](glm::vec3& v) { v *= 2.0f; });
		skyBoxMesh->getMesh()->setPositions(std::move(positions));
    skyBoxMesh->setMaterial(skyBoxMaterial);
		skyBoxMesh->getMesh()->apply();

		graphics->setSkybox(skyboxActor.get());

//		auto cube1 = Primitive::createCube(m_world.get());
//		cubeTransform1 = cube1.getComponent<Transform>();
//		cubeTransform1->setPosition({0.5f, 0.5f, 0.5f});
//		auto cubeMesh1 = cube1.getComponent<MeshRenderer>();
//    cubeMesh1->setMaterial(cubeMaterial);
//
//		auto cube2 = Primitive::createCube(m_world.get());
//		cubeTransform2 = cube2.getComponent<Transform>();
//		cubeTransform2->setPosition({2.0f, 0.5f, 0.0f});
//		auto cubeMesh2 = cube2.getComponent<MeshRenderer>();
//    cubeMesh2->setMaterial(cubeMaterial);

		Scene& scene = (scenes["Test"] = Scene());

		auto ground = Primitive::createPlane();
		auto groundTransform = ground->getComponent<Transform>();
		groundTransform->setScale({50.0f, 0.1f, 50.0f});
		auto groundMesh = ground->getComponent<MeshRenderer>();
		groundMaterial->setTextureScale({50.0f, 50.0f});
    groundMesh->setMaterial(groundMaterial);

    scene.addActor(ground.get());

		auto directionalLight = std::make_unique<Actor>();
		auto directionalLightTransform = directionalLight->getComponent<Transform>();
		auto directionalLightLight = directionalLight->addComponent<Light>();
		directionalLightLight->setColor(Color::fromRGBA32(255, 255, 225, 255));
		directionalLightLight->setIntensity(1.2f);
		directionalLightTransform->rotate({45.0f, 35.0f, 0.0f});

		scene.addActor(directionalLight.get());

		// TODO: Des is bullshit weil die prefabs nach start() zerstört werden
		// TODO: Lösung: Actor direkt in der Szene instanzieren (Kopie oder Move)

		auto camera = std::make_unique<Actor>();
		auto cameraTransform = camera->addComponent<Transform>();
		camera->addComponent<Camera>();
		auto controller = camera->addComponent<FirstPersonController>();
		controller->m_moveSpeed = 3.0f;
		controller->m_mouseSensitivity = 0.1f;

		cameraTransform->translate({0.0f, 0.5f, -2.0f});


		auto model = loadModel("assets/models/nanosuit/nanosuit.obj", cubeMaterial);
		model.front()->getComponent<Transform>()->setScale(glm::vec3(0.1f));
	}

	void update() override
	{
		if (input->isKeyDown(KeyCode::Escape))
		{
			window->close();
		}


//		if (input->isKeyDown(KeyCode::Keypad4))
//		{
//			cubeTransform1->translate({-0.001f * Time::getDeltaTime(), 0.0f, 0.0f});
//		}
//
//		if (input->isKeyDown(KeyCode::Keypad6))
//		{
//			cubeTransform1->translate({0.001f * Time::getDeltaTime(), 0.0f, 0.0f});
//		}
//
//		if (input->isKeyDown(KeyCode::Keypad8))
//		{
//			cubeTransform1->translate({0.0f, 0.0f, 0.001f * Time::getDeltaTime()});
//		}
//
//		if (input->isKeyDown(KeyCode::Keypad2))
//		{
//			cubeTransform1->translate({0.0f, 0.0f, -0.001f * Time::getDeltaTime()});
//		}
//
//		if (input->isKeyDown(KeyCode::Keypad7))
//		{
//			cubeTransform1->rotate({0.0f, -0.1f * Time::getDeltaTime(), 0.0f});
//		}
//
//		if (input->isKeyDown(KeyCode::Keypad9))
//		{
//			cubeTransform1->rotate({0.0f, 0.1f * Time::getDeltaTime(), 0.0f});
//		}
//
//		if (input->isKeyDown(KeyCode::KeypadMinus))
//		{
//			cubeTransform1->rotate({0.1f * Time::getDeltaTime(), 0.0f, 0.0f});
//		}
//
//		if (input->isKeyDown(KeyCode::KeypadPlus))
//		{
//			cubeTransform1->rotate({-0.1f * Time::getDeltaTime(), 0.0f, 0.0f});
//		}
//
//		if (input->isKeyDown(KeyCode::Keypad1))
//		{
//			cubeTransform1->rotate({0.0f, 0.0f, 0.1f * Time::getDeltaTime()});
//		}
//
//		if (input->isKeyDown(KeyCode::Keypad3))
//		{
//			cubeTransform1->rotate({0.0f, 0.0f, -0.1f * Time::getDeltaTime()});
//		}
	}
};

int main(int argc, char* argv[])
{
	SimpleScene app;
	app.run();

	return 0;
}