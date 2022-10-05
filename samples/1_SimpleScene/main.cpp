
#include "Engine.hpp"
#include "Util.hpp"
#include "Primitive.hpp"
#include "Graphics/Light.hpp"
#include "FirstPersonController.hpp"
#include "Graphics/Material.hpp"
#include "Input/Input.hpp"
#include "Graphics/Window.hpp"
#include "Transform.hpp"
#include "Graphics/SDLWindow.hpp"
#include "FirstPersonSystem.hpp"

using namespace aeyon;

class SimpleScene : public Engine
{

public:
    void setup() override
    {
        userSystems.push_back(std::make_unique<FirstPersonSystem>(&sceneLoader, input.get()));
    }

    void start() override
    {
        Resource<Texture> stoneDiffuse = textureCache.load("Bricks18_col",
                                                           {Texture::Type::Tex2D, {"assets/textures/Bricks18_col.jpg"},
                                                            PixelFormat::sRGB8, true});
        Resource<Texture> stoneGloss = textureCache.load("Bricks18_rgh",
                                                         {Texture::Type::Tex2D, {"assets/textures/Bricks18_rgh.jpg"},
                                                          PixelFormat::R8, true});
        Resource<Texture> stoneNormals = textureCache.load("Bricks18_nrm",
                                                           {Texture::Type::Tex2D, {"assets/textures/Bricks18_nrm.jpg"},
                                                            PixelFormat::RGB8, true});
        Resource<Texture> groundDiffuse = textureCache.load("Ground03_col",
                                                            {Texture::Type::Tex2D, {"assets/textures/Ground03_col.jpg"},
                                                             PixelFormat::sRGB8, true});
        Resource<Texture> groundGloss = textureCache.load("Ground03_rgh",
                                                          {Texture::Type::Tex2D, {"assets/textures/Ground03_rgh.jpg"},
                                                           PixelFormat::R8, true});
        Resource<Texture> groundNormals = textureCache.load("Ground03_nrm",
                                                            {Texture::Type::Tex2D, {"assets/textures/Ground03_nrm.jpg"},
                                                             PixelFormat::RGB8, true});
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

        Resource<Material> cubeMaterial(
                std::make_shared<ResourceData<Material>>("CubeMaterial", std::make_unique<Material>(standardShader)));
        cubeMaterial->setParameter("diffuse_texture", stoneDiffuse);
        cubeMaterial->setParameter("specular_texture", stoneGloss);
        cubeMaterial->setParameter("normal_texture", stoneNormals);
        // TODO: Implement default shader values
        cubeMaterial->setParameter("diffuse_color", glm::vec4(1.0f));
        cubeMaterial->setParameter("specular_color", glm::vec4(0.2f));
        cubeMaterial->setParameter("shininess", 8.0f);
        cubeMaterial->setTextureScale(glm::vec2(1.0f));

        Resource<Material> groundMaterial(
                std::make_shared<ResourceData<Material>>("GroundMaterial", std::make_unique<Material>(standardShader)));
        groundMaterial->setParameter("diffuse_texture", groundDiffuse);
        groundMaterial->setParameter("specular_texture", groundGloss);
        groundMaterial->setParameter("normal_texture", groundNormals);
        groundMaterial->setParameter("diffuse_color", glm::vec4(1.0f));
        groundMaterial->setParameter("specular_color", glm::vec4(0.2f));
        groundMaterial->setParameter("shininess", 64.0f);

        Resource<Material> skyBoxMaterial(
                std::make_shared<ResourceData<Material>>("SkyboxMaterial", std::make_unique<Material>(skyboxShader)));
        skyBoxMaterial->setParameter("skybox", skyboxCubemap);


        // TODO: Skybox Komponente erstellen

        Scene &scene = sceneLoader.createScene("Test");
        sceneLoader.setActiveScene("Test");

        Actor ground = Primitive::createPlane();
        ground.setName("Ground");
        auto groundTransform = ground.getComponent<Transform>();
        groundTransform->setScale({50.0f, 0.1f, 50.0f});
        auto groundMesh = ground.getComponent<MeshRenderer>();
        groundMaterial->setTextureScale({50.0f, 50.0f});
        groundMesh->setMaterial(groundMaterial);

        scene.addActor(std::move(ground));

        Actor directionalLight("Directional Light");
        auto directionalLightTransform = directionalLight.getComponent<Transform>();
        auto directionalLightLight = directionalLight.addComponent<Light>();
        directionalLightLight->setColor(Color::fromRGBA32(255, 255, 225, 255));
        directionalLightLight->setIntensity(1.2f);
        directionalLightTransform->rotate({45.0f, 35.0f, 0.0f});

        scene.addActor(std::move(directionalLight));

        Actor camera("Camera");
        auto cameraTransform = camera.getComponent<Transform>();
        cameraTransform->translate({0.0f, 0.5f, -2.0f});
        camera.addComponent<Camera>();
        auto controller = camera.addComponent<FirstPersonController>();
        controller->m_moveSpeed = 3.0f;
        controller->m_mouseSensitivity = 0.1f;

        scene.addActor(std::move(camera));

        std::vector<Actor> model = loadModel("assets/models/nanosuit/nanosuit.obj", cubeMaterial);
        model.front().setName("Nano Suit");
        model.front().getComponent<Transform>()->setScale(glm::vec3(0.1f));

        scene.addActors(std::move(model));
    }

    void update() override
    {
        if (input->isKeyDown(KeyCode::Escape))
        {
            window->close();
        }

        if (input->isKeyDown(KeyCode::LeftAlt))
        {
            SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() == SDL_TRUE ? SDL_FALSE : SDL_TRUE);
        }
    }
};

int main(int argc, char *argv[])
{
    SimpleScene app;
    app.run();

    return 0;
}
