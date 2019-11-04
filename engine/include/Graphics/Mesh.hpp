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

// TODO: Material system still doesn't work as desired. I've removed the const qualifier of getMaterial() which allows
//       for setting material properties after calling getMaterial() in the renderer, but it isn't clear if
//       getMaterial() returns an instantiated or shared material. Is it enough that the user should set this via
//       setMaterial() only? I should clearly rework the 'shared mesh' system...

namespace aeyon
{
	class Mesh
	{
	public:
		static std::vector<VertexAttribute> getVertexAttributesFromFormat(VertexFormat format);

	private:
		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec4> m_colors;
		std::vector<glm::vec2> m_uvs;
		std::vector<glm::vec3> m_tangents;
		std::vector<glm::vec3> m_bitangents;
		std::vector<unsigned int> m_triangles;

		std::vector<Material*> m_materials;
		std::vector<Resource<Material>> m_sharedMaterials;

		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;

		VertexFormat m_vertexFormat;

		Bounds m_bounds;

		bool m_needsUpdate;

	public:
		explicit Mesh(VertexFormat vertexFormat);

		Mesh(const Mesh& other) = delete;
		Mesh& operator=(const Mesh& other) = delete;

		Mesh(Mesh&& other) noexcept;
		Mesh& operator=(Mesh&&) noexcept;

		VertexBuffer* getVertexBuffer()
		{
			return m_vertexBuffer.get();
		}

		IndexBuffer* getIndexBuffer()
		{
			return m_indexBuffer.get();
		}

		void setSharedMaterial(Resource<Material> sharedMaterial);
		template <typename T> void setSharedMaterials(T&& sharedMaterials);

		Resource<Material> getSharedMaterial() const;
		const std::vector<Resource<Material>>& getSharedMaterials() const;

		VertexFormat getVertexFormat() const;
		void setVertexFormat(VertexFormat vertexFormat);

		bool needsUpdate() const;
		void apply();
		void recalculateNormals();
		void recalculateTangents();

		void clear();

		Bounds getBoundingBox() const;

		void setPosition(std::size_t index, const glm::vec3& position);
		void setNormal(std::size_t index, const glm::vec3& normal);
		void setColor(std::size_t index, const glm::vec4& color);
		void setUV(std::size_t index, const glm::vec2& uv);
		void setTangent(std::size_t index, const glm::vec3& tangent);
		void setBitangent(std::size_t index, const glm::vec3& bitangent);

		template <typename T> void setPositions(T&& positions);
		template <typename T> void setNormals(T&& normals);
		template <typename T> void setColors(T&& colors);
		template <typename T> void setUVs(T&& uvs);
		template <typename T> void setTangents(T&& tangents);
		template <typename T> void setBitangents(T&& bitangents);
		template <typename T> void setTriangles(T&& indices);

		const glm::vec3& getPosition(std::size_t index) const;
		const glm::vec3& getNormal(std::size_t index) const;
		const glm::vec4& getColor(std::size_t index) const;
		const glm::vec2& getUV(std::size_t index) const;
		const glm::vec3& getTangent(std::size_t index) const;
		const glm::vec3& getBitangent(std::size_t index) const;

		const std::vector<glm::vec3>& getPositions() const;
		const std::vector<glm::vec3>& getNormals() const;
		const std::vector<glm::vec4>& getColors() const;
		const std::vector<glm::vec2>& getUVs() const;
		const std::vector<glm::vec3>& getTangents() const;
		const std::vector<glm::vec3>& getBitangents() const;
		const std::vector<unsigned int>& getTriangles() const;

		const Bounds& getBounds() const;
	};


	template<typename T>
	void Mesh::setPositions(T&& positions)
	{
		m_positions = std::forward<T>(positions);
		m_needsUpdate = true;
	}

	template<typename T>
	void Mesh::setNormals(T&& normals)
	{
		m_normals = std::forward<T>(normals);
		m_needsUpdate = true;
	}

	template<typename T>
	void Mesh::setColors(T&& colors)
	{
		m_colors = std::forward<T>(colors);
		m_needsUpdate = true;
	}

	template<typename T>
	void Mesh::setUVs(T&& uvs)
	{
		m_uvs = std::forward<T>(uvs);
		m_needsUpdate = true;
	}

	template<typename T>
	void Mesh::setTangents(T&& tangents)
	{
		m_tangents = std::forward<T>(tangents);
		m_needsUpdate = true;
	}

	template<typename T>
	void Mesh::setBitangents(T&& bitangents)
	{
		m_bitangents = std::forward<T>(bitangents);
		m_needsUpdate = true;
	}

	template<typename T>
	void Mesh::setTriangles(T&& indices)
	{
		m_triangles = std::forward<T>(indices);
		m_needsUpdate = true;
	}

	template<typename T>
	void Mesh::setSharedMaterials(T&& sharedMaterials)
	{
		m_sharedMaterials = std::forward<T>(sharedMaterials);
	}
}


#endif //AEYON3D_MESH_HPP
