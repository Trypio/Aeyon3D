//
//
//

#ifndef AEYON3D_PRIMITIVE_HPP
#define AEYON3D_PRIMITIVE_HPP

#include "Transform.hpp"
#include "Graphics/Material.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/MeshRenderer.hpp"
#include "Graphics/Mesh.hpp"
#include "Resource.hpp"
#include <memory>

namespace aeyon::Primitive
{
    // TODO: Supply a white default material for all primitves (or every mesh renderer at creation)

    static Actor createPlane(bool withNormals = true, bool withUVs = true)
    {
        // TODO: Pre-generate meshes as shared resources

        Actor plane;

        VertexFormat format;

        if (withNormals && withUVs)
            format = VertexFormat::P1N1UV1T1B1;
        else if (withNormals)
            format = VertexFormat::P1N1;
        else
            format = VertexFormat::P1;

        Resource<Mesh> mesh(std::make_unique<Mesh>(format));

        mesh->setPositions(std::vector<glm::vec3>{
                glm::vec3(-0.5f, 0.5f, -0.5f),
                glm::vec3(0.5f, 0.5f, -0.5f),
                glm::vec3(0.5f, 0.5f, 0.5f),
                glm::vec3(-0.5f, 0.5f, -0.5f),
                glm::vec3(0.5f, 0.5f, 0.5f),
                glm::vec3(-0.5f, 0.5f, 0.5f),
        });

        if (withNormals)
        {
            mesh->setNormals(std::vector<glm::vec3>{
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
            });
        }

        if (withNormals && withUVs)
        {
            mesh->setUVs(std::vector<glm::vec2>{
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),
            });
        }

        mesh->setTriangles(std::vector<Mesh::TIndex>{
                0, 1, 2, 3, 4, 5
        });

        if (withNormals && withUVs)
            mesh->recalculateTangents();

        mesh->apply();


        plane.addComponent<MeshRenderer>(mesh);

        return plane;
    }

    static Actor createCube(bool withNormals = true, bool withUVs = true)
    {
        // TODO: Pre-generate meshes as shared resources

        Actor cube;

        VertexFormat format;

        if (withNormals && withUVs)
            format = VertexFormat::P1N1UV1T1B1;
        else if (withNormals)
            format = VertexFormat::P1N1;
        else
            format = VertexFormat::P1;

        Resource<Mesh> mesh(std::make_unique<Mesh>(format));

        mesh->setPositions(std::vector<glm::vec3>{
                // Front Face
                glm::vec3(0.5f, -0.5f, 0.5f),
                glm::vec3(-0.5f, -0.5f, 0.5f),
                glm::vec3(-0.5f, 0.5f, 0.5f),
                glm::vec3(0.5f, -0.5f, 0.5f),
                glm::vec3(-0.5f, 0.5f, 0.5f),
                glm::vec3(0.5f, 0.5f, 0.5f),

                // Top Face
                glm::vec3(-0.5f, 0.5f, -0.5f),
                glm::vec3(0.5f, 0.5f, -0.5f),
                glm::vec3(0.5f, 0.5f, 0.5f),
                glm::vec3(-0.5f, 0.5f, -0.5f),
                glm::vec3(0.5f, 0.5f, 0.5f),
                glm::vec3(-0.5f, 0.5f, 0.5f),

                // Left Face
                glm::vec3(-0.5f, -0.5f, 0.5f),
                glm::vec3(-0.5f, -0.5f, -0.5f),
                glm::vec3(-0.5f, 0.5f, -0.5f),
                glm::vec3(-0.5f, -0.5f, 0.5f),
                glm::vec3(-0.5f, 0.5f, -0.5f),
                glm::vec3(-0.5f, 0.5f, 0.5f),

                // Back Face
                glm::vec3(-0.5f, -0.5f, -0.5f),
                glm::vec3(0.5f, -0.5f, -0.5f),
                glm::vec3(0.5f, 0.5f, -0.5f),
                glm::vec3(-0.5f, -0.5f, -0.5f),
                glm::vec3(0.5f, 0.5f, -0.5f),
                glm::vec3(-0.5f, 0.5f, -0.5f),

                // Bottom Face
                glm::vec3(0.5f, -0.5f, -0.5f),
                glm::vec3(-0.5f, -0.5f, -0.5f),
                glm::vec3(-0.5f, -0.5f, 0.5f),
                glm::vec3(0.5f, -0.5f, -0.5f),
                glm::vec3(-0.5f, -0.5f, 0.5f),
                glm::vec3(0.5f, -0.5f, 0.5f),

                // Right Face
                glm::vec3(0.5f, -0.5f, -0.5f),
                glm::vec3(0.5f, -0.5f, 0.5f),
                glm::vec3(0.5f, 0.5f, 0.5f),
                glm::vec3(0.5f, -0.5f, -0.5f),
                glm::vec3(0.5f, 0.5f, 0.5f),
                glm::vec3(0.5f, 0.5f, -0.5f),
        });

        if (withNormals)
        {
            mesh->setNormals(std::vector<glm::vec3>{
                    // Front Face
                    glm::vec3(0.0f, 0.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 1.0f),
                    glm::vec3(0.0f, 0.0f, 1.0f),

                    // Top Face
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),

                    // Left Face
                    glm::vec3(-1.0f, 0.0f, 0.0f),
                    glm::vec3(-1.0f, 0.0f, 0.0f),
                    glm::vec3(-1.0f, 0.0f, 0.0f),
                    glm::vec3(-1.0f, 0.0f, 0.0f),
                    glm::vec3(-1.0f, 0.0f, 0.0f),
                    glm::vec3(-1.0f, 0.0f, 0.0f),

                    // Back Face
                    glm::vec3(0.0f, 0.0f, -1.0f),
                    glm::vec3(0.0f, 0.0f, -1.0f),
                    glm::vec3(0.0f, 0.0f, -1.0f),
                    glm::vec3(0.0f, 0.0f, -1.0f),
                    glm::vec3(0.0f, 0.0f, -1.0f),
                    glm::vec3(0.0f, 0.0f, -1.0f),

                    // Bottom Face
                    glm::vec3(0.0f, -1.0f, 0.0f),
                    glm::vec3(0.0f, -1.0f, 0.0f),
                    glm::vec3(0.0f, -1.0f, 0.0f),
                    glm::vec3(0.0f, -1.0f, 0.0f),
                    glm::vec3(0.0f, -1.0f, 0.0f),
                    glm::vec3(0.0f, -1.0f, 0.0f),

                    // Right Face
                    glm::vec3(1.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 0.0f, 0.0f),
            });
        }

        if (withNormals && withUVs)
        {
            mesh->setUVs(std::vector<glm::vec2>{
                    // Front Face
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    // Top Face
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    // Left Face
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    // Back Face
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    // Bottom Face
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

                    // Right Face
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 0.0f),
                    glm::vec2(1.0f, 1.0f),
                    glm::vec2(0.0f, 1.0f),

            });
        }

        mesh->setTriangles(std::vector<Mesh::TIndex>{
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                31, 32, 33, 34, 35
        });

        if (withNormals && withUVs)
            mesh->recalculateTangents();

        mesh->apply();

        cube.addComponent<MeshRenderer>(mesh);

        return cube;
    }
}

#endif //AEYON3D_PRIMITIVE_HPP
