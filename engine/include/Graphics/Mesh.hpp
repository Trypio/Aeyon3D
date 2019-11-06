//
//
//

#ifndef AEYON3D_MESH_HPP
#define AEYON3D_MESH_HPP

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Material.hpp"
#include "Bounds.hpp"
#include "Resource.hpp"
#include "Types.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace aeyon
{
	class Mesh
	{
	private:
		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<Color> m_colors;
		std::vector<glm::vec2> m_uvs;
		std::vector<glm::vec3> m_tangents;
		std::vector<glm::vec3> m_bitangents;
		std::vector<TIndex> m_triangles;

		std::vector<Resource<Material>> m_materials;

		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;

		VertexFormat m_vertexFormat;
		
		bool m_needsUpdate;

	public:
    static std::vector<VertexAttribute> getVertexAttributesFromFormat(VertexFormat format);

		explicit Mesh(VertexFormat vertexFormat);

		VertexBuffer& getVertexBuffer();
		IndexBuffer& getIndexBuffer();

		void setMaterial(Resource<Material> material);
		void setMaterials(std::vector<Resource<Material>> materials);

		Resource<Material> getMaterial() const;
		const std::vector<Resource<Material>>& getMaterials() const;

		const VertexFormat& getVertexFormat() const;

		bool needsUpdate() const;
		void apply();
		void recalculateNormals();
		void recalculateTangents();

		void clear();

		Bounds getBounds() const;

		void setPosition(std::size_t index, glm::vec3 position);
		void setNormal(std::size_t index, glm::vec3 normal);
		void setColor(std::size_t index, Color color);
		void setUV(std::size_t index, glm::vec2 uv);
		void setTangent(std::size_t index, glm::vec3 tangent);
		void setBitangent(std::size_t index, glm::vec3 bitangent);

		void setPositions(std::vector<glm::vec3> positions);
		void setNormals(std::vector<glm::vec3> normals);
		void setColors(std::vector<Color> colors);
		void setUVs(std::vector<glm::vec2> uvs);
		void setTangents(std::vector<glm::vec3> tangents);
		void setBitangents(std::vector<glm::vec3> bitangents);
		void setTriangles(std::vector<TIndex> indices);

		const glm::vec3& getPosition(std::size_t index) const;
		const glm::vec3& getNormal(std::size_t index) const;
		const Color& getColor(std::size_t index) const;
		const glm::vec2& getUV(std::size_t index) const;
		const glm::vec3& getTangent(std::size_t index) const;
		const glm::vec3& getBitangent(std::size_t index) const;

		const std::vector<glm::vec3>& getPositions() const;
		const std::vector<glm::vec3>& getNormals() const;
		const std::vector<Color>& getColors() const;
		const std::vector<glm::vec2>& getUVs() const;
		const std::vector<glm::vec3>& getTangents() const;
		const std::vector<glm::vec3>& getBitangents() const;
		const std::vector<TIndex>& getTriangles() const;
	};
}


#endif //AEYON3D_MESH_HPP
