#include "Graphics/MeshRenderer.hpp"

namespace aeyon
{
    MeshRenderer::MeshRenderer()
            : m_isSharedMesh(true), m_isSharedMaterial(true), m_areSharedMaterials(true)
    {
    }

    MeshRenderer::MeshRenderer(Resource<Mesh> mesh)
            : m_mesh(std::move(mesh)), m_isSharedMesh(true), m_isSharedMaterial(true), m_areSharedMaterials(true)
    {
    }

    void MeshRenderer::setSharedMesh(Resource<Mesh> mesh)
    {
        m_mesh = std::move(mesh);
        m_isSharedMesh = true;
    }

    void MeshRenderer::setMesh(Resource<Mesh> mesh)
    {
        m_mesh = std::move(mesh);
        m_isSharedMesh = false;
    }

    Resource<Mesh> MeshRenderer::getSharedMesh()
    {
        return m_mesh;
    }

    Resource<Mesh> MeshRenderer::getMesh()
    {
        if (m_isSharedMesh)
        {
            m_mesh = Resource<Mesh>(std::make_shared<Mesh>(*m_mesh));
            m_isSharedMesh = false;
        }

        return m_mesh;
    }

    void MeshRenderer::setSharedMaterial(Resource<Material> material)
    {
        if (m_materials.empty())
        {
            m_materials.push_back(std::move(material));
        }
        else
        {
            m_materials[0] = std::move(material);
        }
        m_isSharedMaterial = true;
    }

    void MeshRenderer::setMaterial(Resource<Material> material)
    {
        if (m_materials.empty())
        {
            m_materials.push_back(std::move(material));
        }
        else
        {
            m_materials[0] = std::move(material);
        }
        m_isSharedMaterial = false;
    }

    Resource<Material> MeshRenderer::getSharedMaterial()
    {
        return m_materials.at(0);
    }

    Resource<Material> MeshRenderer::getMaterial()
    {
        if (m_isSharedMaterial)
        {
            m_materials.at(0) = Resource<Material>(std::make_shared<Material>(*m_materials.at(0)));
            m_isSharedMaterial = false;
        }

        return m_materials.at(0);
    }

    void MeshRenderer::setSharedMaterials(std::vector<Resource<Material>> materials)
    {
        m_materials = std::move(materials);
        m_isSharedMaterial = true;
        m_areSharedMaterials = true;
    }

    void MeshRenderer::setMaterials(std::vector<Resource<Material>> materials)
    {
        m_materials = std::move(materials);
        m_isSharedMaterial = false;
        m_areSharedMaterials = false;
    }

    std::vector<Resource<Material>>& MeshRenderer::getSharedMaterials()
    {
        return m_materials;
    }

    std::vector<Resource<Material>>& MeshRenderer::getMaterials()
    {
        if (!m_areSharedMaterials)
        {
            return m_materials;
        }

        for (auto& m : m_materials)
        {
            m = Resource<Material>(std::make_shared<Material>(*m));
        }

        m_isSharedMaterial = false;
        m_areSharedMaterials = false;

        return m_materials;
    }
}
