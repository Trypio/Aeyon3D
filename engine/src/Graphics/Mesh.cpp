//
//
//

#include "Graphics/Mesh.hpp"
#include <algorithm>
#include <cstring>
#include <Util.hpp>


namespace aeyon
{
	Mesh::Mesh(VertexFormat vertexFormat)
			: m_vertexBuffer(getVertexAttributesFromFormat(vertexFormat)),
				m_vertexFormat(vertexFormat),
				m_needsUpdate(true)
	{
		setSubMeshCount(1);
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

  VertexBuffer& Mesh::getVertexBuffer()
  {
	  // TODO: check usages
    return m_vertexBuffer;
  }

  IndexBuffer& Mesh::getIndexBuffer()
  {
    return m_indexBuffer;
  }

	const VertexFormat& Mesh::getVertexFormat() const
	{
		return m_vertexFormat;
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

		if (m_positions.size() * bytesPerElement != m_vertexBuffer.getSize())
		{
			m_vertexBuffer.reset(m_positions.size() * bytesPerElement);
		}

		std::vector<unsigned char> vertexBufferData(m_positions.size() * bytesPerElement);

		for (std::size_t vIndex = 0; vIndex < m_positions.size(); vIndex++)
    {
      std::memcpy(
          &vertexBufferData[0] + vIndex * bytesPerElement,
          &m_positions[vIndex],
          sizeof(glm::vec3)
          );

		  if (m_vertexFormat == VertexFormat::P1N1 || m_vertexFormat == VertexFormat::P1N1UV1 || m_vertexFormat == VertexFormat::P1N1UV1T1B1)
      {
        std::memcpy(
            &vertexBufferData[0] + vIndex * bytesPerElement + sizeof(glm::vec3),
            &m_normals[vIndex],
            sizeof(glm::vec3)
            );
      }

		  if (m_vertexFormat == VertexFormat::P1N1UV1 || m_vertexFormat == VertexFormat::P1N1UV1T1B1)
      {
        std::memcpy(
            &vertexBufferData[0] + vIndex * bytesPerElement + 2 * sizeof(glm::vec3),
            &m_uvs[vIndex],
            sizeof(glm::vec2)
        );
      }

		  if (m_vertexFormat == VertexFormat::P1N1UV1T1B1)
      {
        std::memcpy(
            &vertexBufferData[0] + vIndex * bytesPerElement + 2 * sizeof(glm::vec3) + sizeof(glm::vec2),
            &m_tangents[vIndex],
            sizeof(glm::vec3)
        );

        std::memcpy(
            &vertexBufferData[0] + vIndex * bytesPerElement + 3 * sizeof(glm::vec3) + sizeof(glm::vec2),
            &m_bitangents[vIndex],
            sizeof(glm::vec3)
        );
      }
    }

    m_vertexBuffer.write(vertexBufferData.data(), vertexBufferData.size(), 0);

		// TODO: Copy data directly into buffer without creating a flattened list first

		auto allTriangles = util::flatten(m_triangles);

		if (allTriangles.size() * sizeof(TIndex) != m_indexBuffer.getSize())
		{
			m_indexBuffer.reset(allTriangles.size() * sizeof(TIndex));
		}

    m_indexBuffer.write(allTriangles.data(), allTriangles.size() * sizeof(TIndex), 0);
		
		m_needsUpdate = false;
	}

	void Mesh::recalculateNormals()
	{
		m_normals.resize(m_positions.size());

		std::fill(m_normals.begin(), m_normals.end(), glm::vec3(0.0f));

		glm::vec3 p0, p1, p2, n;

		for (const auto& triangles : m_triangles)
		{
			for (std::size_t i = 0; i < triangles.size(); i += 3)
			{
				p0 = m_positions[triangles[i]];
				p1 = m_positions[triangles[i + 1]];
				p2 = m_positions[triangles[i + 2]];

				n = glm::normalize(glm::cross(p2 - p0, p1 - p0));

				m_normals[triangles[i]] += n;
				m_normals[triangles[i + 1]] += n;
				m_normals[triangles[i + 2]] += n;
			}

			for (auto& normal : m_normals)
			{
				normal = glm::normalize(normal);
			}
		}


			m_needsUpdate = true;
	}

	void Mesh::recalculateTangents()
	{
		m_tangents.resize(m_positions.size());
		m_bitangents.resize(m_positions.size());

		for (const auto& triangles : m_triangles)
		{
			for (std::size_t i = 0; i < triangles.size(); i += 3)
			{
				glm::vec3& v0 = m_positions[triangles[i]];
				glm::vec3& v1 = m_positions[triangles[i + 1]];
				glm::vec3& v2 = m_positions[triangles[i + 2]];

				glm::vec2& uv0 = m_uvs[triangles[i]];
				glm::vec2& uv1 = m_uvs[triangles[i + 1]];
				glm::vec2& uv2 = m_uvs[triangles[i + 2]];

				glm::vec3 deltaPos1 = v1 - v0;
				glm::vec3 deltaPos2 = v2 - v0;

				glm::vec2 deltaUV1 = uv1 - uv0;
				glm::vec2 deltaUV2 = uv2 - uv0;


				float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
				glm::vec3 tangent = glm::normalize(f * (deltaUV2.y * deltaPos1 - deltaUV1.y * deltaPos2));
				glm::vec3 bitangent = glm::normalize(f * (-deltaUV2.x * deltaPos1 + deltaUV1.x * deltaPos2));

				m_tangents[triangles[i]] = tangent;
				m_tangents[triangles[i + 1]] = tangent;
				m_tangents[triangles[i + 2]] = tangent;

				m_bitangents[triangles[i]] = bitangent;
				m_bitangents[triangles[i + 1]] = bitangent;
				m_bitangents[triangles[i + 2]] = bitangent;
			}
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
	
	Bounds Mesh::getBounds() const
	{
	  return Bounds::fromPoints(m_positions);
	}

  void Mesh::setPosition(std::size_t index, glm::vec3 position)
  {
    m_positions.at(index) = std::move(position);
    m_needsUpdate = true;
  }
  
  void Mesh::setNormal(std::size_t index, glm::vec3 normal)
  {
    m_normals.at(index) = std::move(normal);
    m_needsUpdate = true;
  }

  void Mesh::setColor(std::size_t index, Color color)
  {
    m_colors.at(index) = std::move(color);
    m_needsUpdate = true;
  }

  void Mesh::setUV(std::size_t index, glm::vec2 uv)
  {
    m_uvs.at(index) = std::move(uv);
    m_needsUpdate = true;
  }

  void Mesh::setTangent(std::size_t index, glm::vec3 tangent)
  {
    m_tangents.at(index) = std::move(tangent);
    m_needsUpdate = true;
  }
  void Mesh::setBitangent(std::size_t index, glm::vec3 bitangent)
  {
    m_bitangents.at(index) = std::move(bitangent);
    m_needsUpdate = true;
  }
	
  void Mesh::setPositions(std::vector<glm::vec3> positions)
  {
    m_positions = std::move(positions);
    m_needsUpdate = true;
  }
  
  void Mesh::setNormals(std::vector<glm::vec3> normals)
  {
    m_normals = std::move(normals);
    m_needsUpdate = true;
  }
  
  void Mesh::setColors(std::vector<Color> colors)
  {
    m_colors = std::move(colors);
    m_needsUpdate = true;
  }
  
  void Mesh::setUVs(std::vector<glm::vec2> uvs)
  {
    m_uvs = std::move(uvs);
    m_needsUpdate = true;
  }
  
  void Mesh::setTangents(std::vector<glm::vec3> tangents)
  {
    m_tangents = std::move(tangents);
    m_needsUpdate = true;
  }
  
  void Mesh::setBitangents(std::vector<glm::vec3> bitangents)
  {
    m_bitangents = std::move(bitangents);
    m_needsUpdate = true;
  }
  
  void Mesh::setTriangles(std::vector<TIndex> indices, std::size_t submesh)
  {
    m_triangles.at(submesh) = std::move(indices);
    m_needsUpdate = true;
  }
  
	
	const glm::vec3& Mesh::getPosition(std::size_t index) const
	{
		return m_positions.at(index);
	}

  const glm::vec3& Mesh::getNormal(std::size_t index) const
  {
    return m_normals.at(index);
  }

  const Color& Mesh::getColor(std::size_t index) const
  {
    return m_colors.at(index);
  }

  const glm::vec2& Mesh::getUV(std::size_t index) const
  {
    return m_uvs.at(index);
  }

  const glm::vec3& Mesh::getTangent(std::size_t index) const
  {
    return m_tangents.at(index);
  }
  
  const glm::vec3& Mesh::getBitangent(std::size_t index) const
  {
    return m_bitangents.at(index);
  }


  const std::vector<glm::vec3>& Mesh::getPositions() const
	{
		return m_positions;
	}

	const std::vector<glm::vec3>& Mesh::getNormals() const
	{
		return m_normals;
	}

	const std::vector<Color>& Mesh::getColors() const
	{
		return m_colors;
	}

	const std::vector<glm::vec2>& Mesh::getUVs() const
	{
		return m_uvs;
	}

	const std::vector<glm::vec3>& Mesh::getTangents() const
	{
		return m_tangents;
	}

	const std::vector<glm::vec3>& Mesh::getBitangents() const
	{
		return m_bitangents;
	}

	void Mesh::setSubMeshCount(std::size_t count)
	{
		m_triangles.resize(count);
	}

	const std::vector<TIndex>& Mesh::getTriangles(std::size_t submesh) const
	{
		return m_triangles.at(submesh);
	}

	std::size_t Mesh::getSubMeshCount() const
	{
		return m_triangles.size();
	}

	unsigned int Mesh::getSubMeshOffset(std::size_t submesh) const
	{
		unsigned int offset = 0;
		for (std::size_t i = 0; i < submesh; i++)
		{
			offset += m_triangles.at(i).size();
		}

		return offset;
	}
}