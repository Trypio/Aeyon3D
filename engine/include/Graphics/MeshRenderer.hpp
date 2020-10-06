//
//
//

#ifndef AEYON3D_MESHRENDERER_HPP
#define AEYON3D_MESHRENDERER_HPP

#include "Component.hpp"
#include "Resource.hpp"
#include "Mesh.hpp"
#include "Material.hpp"

namespace aeyon
{
	class MeshRenderer : public Component
	{
	private:
		Resource<Mesh> m_mesh;
		std::vector<Resource<Material>> m_materials;

	public:
		MeshRenderer() = default;

		explicit MeshRenderer(Resource<Mesh> mesh, std::vector<Resource<Material>> materials = {})
		: m_mesh(std::move(mesh)), m_materials(std::move(materials))
		{
		}

		void setMesh(Resource<Mesh> mesh)
		{
			m_mesh = std::move(mesh);
		}

		Resource<Mesh> getMesh() const
		{
			return m_mesh;
		}

		void setMaterial(Resource<Material> material)
		{
			if (m_materials.empty())
			{
				m_materials.push_back(std::move(material));
			}
			else
			{
				m_materials[0] = std::move(material);
			}
		}

		void setMaterials(std::vector<Resource<Material>> materials)
		{
			m_materials = std::move(materials);
		}

		Resource<Material> getMaterial() const
		{
			return m_materials.at(0);
		}

		const std::vector<Resource<Material>>& getMaterials() const
		{
			return m_materials;
		}
	};
}


#endif //AEYON3D_MESHRENDERER_HPP
