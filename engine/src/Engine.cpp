//
//
//

#define GLM_ENABLE_EXPERIMENTAL

#include "Engine.hpp"
#include "Time.hpp"
#include "FirstPersonSystem.hpp"
#include "CollisionSystem.hpp"
#include "Graphics/MeshRenderer.hpp"
#include "Graphics/GraphicsSystem.hpp"
#include "Input/SDLInput.hpp"
#include "SDLWindow.hpp"
#include "GUI/GUISystem.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <spdlog/spdlog.h>

namespace aeyon
{
	void Engine::setup()
	{
		// To be overridden by the user
	}

	void Engine::start()
	{
		// To be overridden by the user
	}

	void Engine::update()
	{
		// To be overridden by the user
	}

	void Engine::fixedUpdate()
	{
		// To be overridden by the user
	}

	void Engine::lateUpdate()
	{
		// To be overridden by the user
	}

	void Engine::run()
	{
		SDL_Init(SDL_INIT_VIDEO);

		spdlog::info("Welcome to Aeyon3D");

		input = std::make_unique<SDLInput>();

		// Query display mode for fullscreen initialization (or setting custom refresh rate)
//		SDL_DisplayMode displayMode;
//		SDL_GetCurrentDisplayMode(0, &displayMode);
//		std::cout << "Native: " << displayMode.w << " x " << displayMode.h << " @ " << displayMode.refresh_rate << "hz" << "\n";

		window = std::make_unique<SDLWindow>(
				"Aeyon3D",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				1024, 768,
				SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
		);

		//sdlWindow->setWindowMode(Window::WindowMode::Fullscreen);

		graphics = std::make_unique<GraphicsSystem>(currentScene, window.get());
		gui = std::make_unique<GUISystem>(graphics.get());
		collisions = std::make_unique<CollisionSystem>(currentScene);

		userSystems.push_back(std::make_unique<FirstPersonSystem>(currentScene, input.get()));

		graphics->setup();
		gui->setup();
		collisions->setup();
		for (auto& system : userSystems)
		{
			system->setup();
		}
		setup();

		graphics->start();
		gui->start();
		collisions->start();
		for (auto& system : userSystems)
		{
			system->start();
		}
		start();

		while (!window->shouldClose())
		{
			Time::update();
			input->update();
			update();
			for (auto& system : userSystems)
			{
				system->update();
			}
			collisions->update();
			gui->update();
			graphics->update();

			lateUpdate();

			window->swapBuffers();
		}

		SDL_Quit();
	}




	std::vector<std::unique_ptr<Actor>> Engine::loadModel(const std::string& path, Resource<Material> material)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(path,
																						 aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_MakeLeftHanded);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			throw std::runtime_error(std::string("ERROR::ASSIMP::") + importer.GetErrorString());
		}

		std::unique_ptr<Actor> root = std::make_unique<Actor>();
		std::vector<std::unique_ptr<Actor>> list;

		processNode(scene, scene->mRootNode, *root), list, material);

		list.insert(list.begin(), std::move(root));

		return list;
	}

	void Engine::processNode(const aiScene* scene, const aiNode* node, Actor& root, std::vector<std::unique_ptr<Actor>>& actors, Resource<Material> material)
	{
		auto transform = root.getComponent<Transform>();

		// Extract Transform
		aiVector3D scaling, position;
		aiQuaternion rotation;

		node->mTransformation.Decompose(scaling, rotation, position);

		transform->setScale(glm::vec3(scaling.x, scaling.y, scaling.z));
		transform->setRotation(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
		transform->setPosition(glm::vec3(position.x, position.y, position.z));

		// Extract Mesh
		if (node->mNumMeshes > 0)
		{
			Resource<Mesh> mesh(
					std::make_shared<ResourceData<Mesh>>("nanosuit", std::make_unique<Mesh>(VertexFormat::P1N1UV1T1B1)));

			mesh->setSubMeshCount(node->mNumMeshes);

			// Iterate over submeshes
			std::vector<glm::vec3> positions, normals, tangents, bitangents;
			std::vector<glm::vec2> uvs;
			std::vector<std::vector<unsigned int>> subMeshTriangles(node->mNumMeshes);

			for (unsigned int iMesh = 0; iMesh < node->mNumMeshes; iMesh++)
			{
				aiMesh* submesh = scene->mMeshes[node->mMeshes[iMesh]];

				for (unsigned int iVertex = 0; iVertex < submesh->mNumVertices; iVertex++)
				{
					positions.emplace_back(submesh->mVertices[iVertex].x, submesh->mVertices[iVertex].y,
																 submesh->mVertices[iVertex].z);
				}

				for (unsigned int iFace = 0; iFace < submesh->mNumFaces; iFace++)
				{
					for (unsigned int iIndex = 0; iIndex < submesh->mFaces[iFace].mNumIndices; iIndex++)
					{
						subMeshTriangles[iMesh].emplace_back(submesh->mFaces[iFace].mIndices[iIndex]);
					}
				}

				if (submesh->HasNormals())
				{
					for (unsigned int iTangent = 0; iTangent < submesh->mNumVertices; iTangent++)
					{
						normals.emplace_back(submesh->mNormals[iTangent].x, submesh->mNormals[iTangent].y,
																 submesh->mNormals[iTangent].z);
					}
				}

				if (submesh->HasTangentsAndBitangents())
				{
					for (unsigned int iTangent = 0; iTangent < submesh->mNumVertices; iTangent++)
					{
						tangents.emplace_back(submesh->mTangents[iTangent].x, submesh->mTangents[iTangent].y,
																	submesh->mTangents[iTangent].z);
					}

					for (unsigned int iBitangent = 0; iBitangent < submesh->mNumVertices; iBitangent++)
					{
						bitangents.emplace_back(submesh->mBitangents[iBitangent].x, submesh->mBitangents[iBitangent].y,
																		submesh->mBitangents[iBitangent].z);
					}
				}


				// TODO: Add support for multiple UV sets


				if (submesh->HasTextureCoords(0))
				{
					for (unsigned int iUV = 0; iUV < submesh->mNumVertices; iUV++)
					{
						uvs.emplace_back(submesh->mTextureCoords[0][iUV].x, submesh->mTextureCoords[0][iUV].y);
					}
				}
			}

			mesh->setPositions(std::move(positions));
			for (std::size_t i = 0; i < subMeshTriangles.size(); i++)
			{
				mesh->setTriangles(std::move(subMeshTriangles[i]), i);
			}

			if (!normals.empty())
			{
				mesh->setNormals(std::move(normals));
			}
			else
			{
				mesh->recalculateNormals();
			}

			mesh->setUVs(std::move(uvs));

			if (!tangents.empty() && !bitangents.empty())
			{
				mesh->setTangents(std::move(tangents));
				mesh->setBitangents(std::move(bitangents));
			}
			else if (!mesh->getUVs().empty())
			{
				mesh->recalculateTangents();
			}



			mesh->apply();

			auto meshRenderer = root.addComponent<MeshRenderer>();
			meshRenderer->setMesh(mesh);
			meshRenderer->setMaterial(material);
		}

		for (unsigned int iChild = 0; iChild < node->mNumChildren; iChild++)
		{
			auto child = std::make_unique<Actor>();
			child->addComponent<Transform>()->setParent(transform);
			processNode(scene, node->mChildren[iChild], *child, actors, material);
		}
	}
}
