#ifndef AEYON3D_MESHRENDERER_HPP
#define AEYON3D_MESHRENDERER_HPP

#include "Component.hpp"
#include "Resource.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include <vector>

namespace aeyon
{
	class MeshRenderer : public Component
	{
	private:
		Resource<Mesh> m_mesh;
        bool m_isSharedMesh, m_isSharedMaterial, m_areSharedMaterials;
		std::vector<Resource<Material>> m_materials;

	public:
		explicit MeshRenderer(Actor* actor);
		MeshRenderer(Actor* actor, Resource<Mesh> mesh);

        void setSharedMesh(Resource<Mesh> mesh);
		void setMesh(Resource<Mesh> mesh);
		Resource<Mesh> getSharedMesh();
        Resource<Mesh> getMesh();

        void setSharedMaterial(Resource<Material> material);
		void setMaterial(Resource<Material> material);
        Resource<Material> getSharedMaterial();
        Resource<Material> getMaterial();

        void setSharedMaterials(std::vector<Resource<Material>> materials);
        void setMaterials(std::vector<Resource<Material>> materials);
        std::vector<Resource<Material>>& getSharedMaterials();
        std::vector<Resource<Material>>& getMaterials();
	};
}


#endif //AEYON3D_MESHRENDERER_HPP
