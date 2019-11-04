//
//
//

#include "Graphics/Mesh.hpp"
#include <algorithm>
#include <Graphics/Mesh.hpp>


namespace aeyon
{
	Mesh::Mesh(VertexFormat vertexFormat)
			: m_vertexBuffer(std::make_unique<VertexBuffer>(getVertexAttributesFromFormat(vertexFormat))),
				m_indexBuffer(std::make_unique<IndexBuffer>()),
				m_vertexFormat(vertexFormat),
				m_needsUpdate(true)
	{
	}

	Mesh::Mesh(Mesh&& other) noexcept
	{
		*this = std::move(other);
	}

	Mesh& Mesh::operator=(Mesh&& other) noexcept
	{
		m_positions = std::move(other.m_positions);
		m_normals = std::move(other.m_normals);
		m_colors = std::move(other.m_colors);
		m_uvs = std::move(other.m_uvs);
		m_tangents = std::move(other.m_tangents);
		m_bitangents = std::move(other.m_bitangents);
		m_vertexFormat = other.m_vertexFormat;
		m_needsUpdate = other.m_needsUpdate;
		m_triangles = std::move(other.m_triangles);
		m_materials = std::move(other.m_materials);
		m_sharedMaterials = std::move(other.m_sharedMaterials);
		m_vertexBuffer = std::move(m_vertexBuffer);
		m_indexBuffer = std::move(m_indexBuffer);

		other.m_needsUpdate = false;

		return *this;
	}


	void Mesh::setSharedMaterial(Resource<Material> sharedMaterial)
	{
		if (m_sharedMaterials.empty())
			m_sharedMaterials.push_back(sharedMaterial);
		else
			m_sharedMaterials[0] = sharedMaterial;
	}


	Resource<Material> Mesh::getSharedMaterial() const
	{
		// TODO: Request a "Missing Material" if there are no sharedMaterials
		return m_sharedMaterials.at(0);
	}


	const std::vector<Resource<Material>>& Mesh::getSharedMaterials() const
	{
		return m_sharedMaterials;
	}

	VertexFormat Mesh::getVertexFormat() const
	{
		return m_vertexFormat;
	}

	void Mesh::setVertexFormat(VertexFormat vertexFormat)
	{
		m_vertexBuffer->setVertexAttributes(getVertexAttributesFromFormat(vertexFormat));
		m_vertexFormat = vertexFormat;
	}

	bool Mesh::needsUpdate() const
	{
		return m_needsUpdate;
	}

	void Mesh::apply()
	{
		std::size_t bytesPerElement;

		switch (m_vertexFormat)
		{
			case VertexFormat::P1:
				bytesPerElement = sizeof(glm::vec3);
				break;
			case VertexFormat::P1N1:
				bytesPerElement = 2 * sizeof(glm::vec3);
				break;
			case VertexFormat::P1N1UV1:
				bytesPerElement = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);
				break;
			case VertexFormat::P1N1UV1T1B1:
				bytesPerElement = 4 * sizeof(glm::vec3) + sizeof(glm::vec2);
				break;
		}

		if (m_positions.size() * bytesPerElement != m_vertexBuffer->getSize())
		{
			m_vertexBuffer->reset(m_positions.size() * bytesPerElement);
		}

		// TODO: This is very inefficient
		std::vector<float> vertexBufferData;

		if (m_vertexFormat == VertexFormat::P1)
		{
			for (std::size_t vIndex = 0; vIndex < m_positions.size(); vIndex++)
			{
				vertexBufferData.push_back(m_positions[vIndex].x);
				vertexBufferData.push_back(m_positions[vIndex].y);
				vertexBufferData.push_back(m_positions[vIndex].z);
			}
		}
		else if (m_vertexFormat == VertexFormat::P1N1)
		{
			for (std::size_t vIndex = 0; vIndex < m_positions.size(); vIndex++)
			{
				vertexBufferData.push_back(m_positions[vIndex].x);
				vertexBufferData.push_back(m_positions[vIndex].y);
				vertexBufferData.push_back(m_positions[vIndex].z);

				vertexBufferData.push_back(m_normals[vIndex].x);
				vertexBufferData.push_back(m_normals[vIndex].y);
				vertexBufferData.push_back(m_normals[vIndex].z);
			}
		}
		else if (m_vertexFormat == VertexFormat::P1N1UV1)
		{
			for (std::size_t vIndex = 0; vIndex < m_positions.size(); vIndex++)
			{
				vertexBufferData.push_back(m_positions[vIndex].x);
				vertexBufferData.push_back(m_positions[vIndex].y);
				vertexBufferData.push_back(m_positions[vIndex].z);

				vertexBufferData.push_back(m_normals[vIndex].x);
				vertexBufferData.push_back(m_normals[vIndex].y);
				vertexBufferData.push_back(m_normals[vIndex].z);

				vertexBufferData.push_back(m_uvs[vIndex].x);
				vertexBufferData.push_back(m_uvs[vIndex].y);
			}
		}
		else if (m_vertexFormat == VertexFormat::P1N1UV1T1B1)
		{
			for (std::size_t vIndex = 0; vIndex < m_positions.size(); vIndex++)
			{
				vertexBufferData.push_back(m_positions[vIndex].x);
				vertexBufferData.push_back(m_positions[vIndex].y);
				vertexBufferData.push_back(m_positions[vIndex].z);

				vertexBufferData.push_back(m_normals[vIndex].x);
				vertexBufferData.push_back(m_normals[vIndex].y);
				vertexBufferData.push_back(m_normals[vIndex].z);

				vertexBufferData.push_back(m_uvs[vIndex].x);
				vertexBufferData.push_back(m_uvs[vIndex].y);

				vertexBufferData.push_back(m_tangents[vIndex].x);
				vertexBufferData.push_back(m_tangents[vIndex].y);
				vertexBufferData.push_back(m_tangents[vIndex].z);

				vertexBufferData.push_back(m_bitangents[vIndex].x);
				vertexBufferData.push_back(m_bitangents[vIndex].y);
				vertexBufferData.push_back(m_bitangents[vIndex].z);

			}
		}


		m_vertexBuffer->write(0, vertexBufferData.size() * sizeof(float), vertexBufferData.data());


		if (m_triangles.size() * sizeof(unsigned int) != m_indexBuffer->getSize())
		{
			m_indexBuffer->reset(m_triangles.size() * sizeof(unsigned int));
		}

		m_indexBuffer->write(0, m_triangles.size() * sizeof(unsigned int), m_triangles.data());


		glm::vec3 min(std::numeric_limits<float>::min()), max(std::numeric_limits<float>::max());

		for (const auto& pos : m_positions)
		{
			if (pos.x < min.x)
				min.x = pos.x;

			if (pos.y < min.y)
				min.y = pos.y;

			if (pos.z < min.z)
				min.z = pos.z;

			if (pos.x > max.x)
				max.x = pos.x;

			if (pos.y > max.y)
				max.y = pos.y;

			if (pos.z > max.z)
				max.z = pos.z;
		}

		m_bounds.setCenter(glm::vec3(0.0f));
		m_bounds.setSize(max - min);

		m_needsUpdate = false;
	}

	void Mesh::recalculateNormals()
	{
		m_normals.resize(m_positions.size());

		std::fill(m_normals.begin(), m_normals.end(), glm::vec3(0.0f));

		glm::vec3 p0, p1, p2, n;

			for (std::size_t i = 0; i < m_triangles.size(); i += 3)
			{
				p0 = m_positions[m_triangles[i]];
				p1 = m_positions[m_triangles[i + 1]];
				p2 = m_positions[m_triangles[i + 2]];

				n = glm::normalize(glm::cross(p1 - p0, p2 - p0));

				m_normals[m_triangles[i]] += n;
				m_normals[m_triangles[i + 1]] += n;
				m_normals[m_triangles[i + 2]] += n;
			}

			for (auto& normal : m_normals)
			{
				normal = glm::normalize(normal);
			}

			m_needsUpdate = true;
	}

	void Mesh::recalculateTangents()
	{
		m_tangents.resize(m_positions.size());
		m_bitangents.resize(m_positions.size());

		for (unsigned int i = 0; i < m_triangles.size(); i += 3)
		{
			glm::vec3& v0 = m_positions[m_triangles[i]];
			glm::vec3& v1 = m_positions[m_triangles[i + 1]];
			glm::vec3& v2 = m_positions[m_triangles[i + 2]];

			glm::vec2& uv0 = m_uvs[m_triangles[i]];
			glm::vec2& uv1 = m_uvs[m_triangles[i + 1]];
			glm::vec2& uv2 = m_uvs[m_triangles[i + 2]];

			glm::vec3 deltaPos1 = v1 - v0;
			glm::vec3 deltaPos2 = v2 - v0;

			glm::vec2 deltaUV1 = uv1 - uv0;
			glm::vec2 deltaUV2 = uv2 - uv0;


			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
			glm::vec3 tangent = glm::normalize(f * (deltaUV2.y * deltaPos1 - deltaUV1.y * deltaPos2));
			glm::vec3 bitangent = glm::normalize(f * (-deltaUV2.x * deltaPos1 + deltaUV1.x * deltaPos2));

			m_tangents[m_triangles[i]] = tangent;
			m_tangents[m_triangles[i + 1]] = tangent;
			m_tangents[m_triangles[i + 2]] = tangent;

			m_bitangents[m_triangles[i]] = bitangent;
			m_bitangents[m_triangles[i + 1]] = bitangent;
			m_bitangents[m_triangles[i + 2]] = bitangent;
		}

		m_needsUpdate = true;
	}


	void Mesh::clear()
	{
		m_positions.clear();
		m_normals.clear();
		m_colors.clear();
		m_uvs.clear();
		m_tangents.clear();
		m_bitangents.clear();
		m_triangles.clear();

		m_needsUpdate = true;
	}


	Bounds Mesh::getBoundingBox() const
	{
		Bounds bb;
		
		glm::vec3 pMin(std::numeric_limits<float>::max()), pMax(std::numeric_limits<float>::min());
		
		for (const auto& p : m_positions)
		{
			if (p.x < pMin.x)
				pMin.x = p.x;
			if (p.y < pMin.y)
				pMin.y = p.y;
			if (p.z < pMin.z)
				pMin.z = p.z;

			if (p.x > pMax.x)
				pMax.x = p.x;
			if (p.y > pMax.y)
				pMax.y = p.y;
			if (p.z > pMax.z)
				pMax.z = p.z;
		}

		bb.setSize(pMax - pMin);
		bb.setCenter(pMax - bb.getExtents());

		return bb;
	}

	const glm::vec3& Mesh::getPosition(std::size_t index) const
	{
		return m_positions[index];
	}

	const std::vector<glm::vec3>& Mesh::getPositions() const
	{
		return m_positions;
	}

	void Mesh::setPosition(std::size_t index, const glm::vec3& position)
	{
		m_positions[index] = position;
		m_needsUpdate = true;
	}

	const glm::vec3& Mesh::getNormal(std::size_t index) const
	{
		return m_normals[index];
	}

	const std::vector<glm::vec3>& Mesh::getNormals() const
	{
		return m_normals;
	}

	void Mesh::setNormal(std::size_t index, const glm::vec3& normal)
	{
		m_normals[index] = normal;
		m_needsUpdate = true;
	}

	const glm::vec4& Mesh::getColor(std::size_t index) const
	{
		return m_colors[index];
	}

	const std::vector<glm::vec4>& Mesh::getColors() const
	{
		return m_colors;
	}

	void Mesh::setColor(std::size_t index, const glm::vec4& color)
	{
		m_colors[index] = color;
		m_needsUpdate = true;
	}

	const glm::vec2& Mesh::getUV(std::size_t index) const
	{
		return m_uvs[index];
	}

	const std::vector<glm::vec2>& Mesh::getUVs() const
	{
		return m_uvs;
	}

	void Mesh::setUV(std::size_t index, const glm::vec2& uv)
	{
		m_uvs[index] = uv;
		m_needsUpdate = true;
	}

	const glm::vec3& Mesh::getTangent(std::size_t index) const
	{
		return m_tangents[index];
	}

	const std::vector<glm::vec3>& Mesh::getTangents() const
	{
		return m_tangents;
	}

	void Mesh::setTangent(std::size_t index, const glm::vec3& tangent)
	{
		m_tangents[index] = tangent;
		m_needsUpdate = true;
	}


	const glm::vec3& Mesh::getBitangent(std::size_t index) const
	{
		return m_bitangents[index];
	}

	const std::vector<glm::vec3>& Mesh::getBitangents() const
	{
		return m_bitangents;
	}

	void Mesh::setBitangent(std::size_t index, const glm::vec3& bitangent)
	{
		m_bitangents[index] = bitangent;
		m_needsUpdate = true;
	}

	const std::vector<unsigned int>& Mesh::getTriangles() const
	{
		return m_triangles;
	}

	std::vector<VertexAttribute> Mesh::getVertexAttributesFromFormat(VertexFormat format)
	{
		if (format == VertexFormat::P1)
		{
			return {
					{ VertexType::Float, 3, false }
			};
		}
		else if (format == VertexFormat::P1N1)
		{
			return {
					{ VertexType::Float, 3, false },
					{ VertexType::Float, 3, false }
			};
		}
		else if (format == VertexFormat::P1N1UV1)
		{
			return {
					{ VertexType::Float, 3, false },
					{ VertexType::Float, 3, false },
					{ VertexType::Float, 2, false }
			};
		}
		else if (format == VertexFormat::P1N1UV1T1B1)
		{
			return {
					{ VertexType::Float, 3, false },
					{ VertexType::Float, 3, false },
					{ VertexType::Float, 2, false },
					{ VertexType::Float, 3, false },
					{ VertexType::Float, 3, false }
			};
		}
		else
		{
			return std::vector<VertexAttribute>();
		}
	}

	const Bounds& Mesh::getBounds() const
	{
		return m_bounds;
	}
}