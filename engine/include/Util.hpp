//
//
//

#ifndef AEYON3D_UTIL_HPP
#define AEYON3D_UTIL_HPP

#include "Graphics/Texture.hpp"
#include <string>
#include <memory>
#include "stb_image.h"
#include <fstream>
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include "Graphics/Mesh.hpp"
#include <iostream>
#include "Graphics/Shader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Actor.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/MeshRenderer.hpp"

namespace aeyon
{
	namespace util
	{
		static std::unique_ptr<Texture> loadTexture2DFromFile(const std::string& path, const PixelFormat& format,
																													bool releaseMemory = false)
		{
			stbi_set_flip_vertically_on_load(1);

			int width, height, channels;
			auto data = stbi_load(path.c_str(), &width, &height, &channels, static_cast<int>(format.getNumChannels()));

			stbi_set_flip_vertically_on_load(0);

			if (!data)
			{
				throw std::runtime_error(path + " could not be loaded!");
			}

			auto tex = std::make_unique<Texture>(Texture::Type::Tex2D, format, width, height);
			tex->setPixelDataRaw(data);

			stbi_image_free(data);

			tex->apply(releaseMemory);

			return tex;
		}

		static std::unique_ptr<Texture> loadCubeMapFromFiles(const std::vector<std::string>& paths,
				                                                 const PixelFormat& format,
				                                                 bool releaseMemory = false)
		{
			std::unique_ptr<Texture> tex = nullptr;

			for (std::size_t face = 0; face < 6; face++)
			{
				int width, height, channels;
				auto data = stbi_load(paths[face].c_str(), &width, &height, &channels, static_cast<int>(format.getNumChannels()));

				if (!tex)
				{
					tex = std::make_unique<Texture>(Texture::Type::Cube, format, width, height);
					tex->setWrapMode(Texture::WrapMode::Clamp);
					tex->setAnisoLevel(1.0f);
					tex->setFilterMode(Texture::FilterMode::Bilinear);
				}

				tex->setPixelDataRaw(data, face);

				stbi_image_free(data);
			}

			tex->apply(releaseMemory);


			return tex;
		}


		static std::unique_ptr<Shader> loadShaderFromFile(const std::string& path)
		{
			std::ifstream file(path);

			if (!file)
			{
				throw std::runtime_error(std::string("Shader file ") + path + " could not be opened");
			}

			std::string code = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

			file.close();

			return std::make_unique<Shader>(code);
		}

		template <typename T>
		static std::vector<T> flatten(const std::vector<std::vector<T>>& v)
		{
			std::size_t totalSize = 0;

			for (const auto& sub : v)
			{
				totalSize += sub.size();
			}

			std::vector<T> result;
			result.reserve(totalSize);

			for (const auto& sub : v)
			{
				result.insert(result.end(), sub.begin(), sub.end());
			}

			return result;
		}

		static void dumpGLSL(const std::string& filename, const std::string& code)
		{
			std::ofstream ofs(std::string("shaders/dump/") + filename);

			if (!ofs)
			{
				std::cout << "Shader Dump: File " << filename << " could not be created" << std::endl;
				return;
			}

			ofs << code;
		}

		static bool endsWith(const std::string& str, const std::string& ending)
		{
			if (str.length() >= ending.length())
			{
				return (0 == str.compare(str.length() - ending.length(), ending.length(), ending));
			}
			else
			{
				return false;
			}
		}

        static Actor* processNode(const aiScene* scene, const aiNode* node, std::vector<Actor>& list, const Resource<Material>& material)
        {
            auto& actor = list.emplace_back();
            actor.setName(node->mName.C_Str());
            auto transform = actor.getComponent<Transform>();

            // Extract Transform
            aiVector3D scaling, position;
            aiQuaternion rotation;

            node->mTransformation.Decompose(scaling, rotation, position);

            transform->setLocalScale(glm::vec3(scaling.x, scaling.y, scaling.z));
            transform->setLocalRotation(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
            transform->setLocalPosition(glm::vec3(position.x, position.y, position.z));

            // Extract Mesh
            if (node->mNumMeshes > 0)
            {
                Resource<Mesh> mesh(std::make_unique<Mesh>(VertexFormat::P1N1UV1T1B1));

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

                auto meshRenderer = actor.addComponent<MeshRenderer>();
                meshRenderer->setSharedMesh(mesh);
                meshRenderer->setSharedMaterial(material);
            }

            for (unsigned int iChild = 0; iChild < node->mNumChildren; iChild++)
            {
                Actor* child = processNode(scene, node->mChildren[iChild], list, material);
                child->getComponent<Transform>()->setParent(transform);
            }

            return &actor;
        }

        static Actor* loadModel(const std::string& path, std::vector<Actor>& list, const Resource<Material>& material)
        {
            Assimp::Importer importer;

            const aiScene* scene = importer.ReadFile(path,
                                                     aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_MakeLeftHanded);

            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                throw std::runtime_error(std::string("ERROR::ASSIMP::") + importer.GetErrorString());
            }

            Actor* actor = processNode(scene, scene->mRootNode, list, material);

            return actor;
        }
	}
}

#endif //AEYON3D_UTIL_HPP
