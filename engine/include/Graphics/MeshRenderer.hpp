//
//
//

#ifndef AEYON3D_MESHRENDERER_HPP
#define AEYON3D_MESHRENDERER_HPP

#include "ECS/Component.hpp"
#include "Resource.hpp"
#include "Mesh.hpp"

namespace aeyon
{
	class MeshRenderer : public Component<MeshRenderer>
	{
	private:
		Resource<Mesh> m_mesh;

	public:
		MeshRenderer() = default;

		explicit MeshRenderer(Resource<Mesh> mesh)
		: m_mesh(std::move(mesh))
		{
		}

		void setSharedMesh(Resource<Mesh> mesh)
		{
			m_mesh = std::move(mesh);
		}

		Resource<Mesh> getSharedMesh() const
		{
			return m_mesh;
		}
	};
}


#endif //AEYON3D_MESHRENDERER_HPP
