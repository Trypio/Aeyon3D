//
//
//

#include "Bounds.hpp"
#include <stdexcept>
#include <vector>

namespace aeyon
{
	Bounds::Bounds()
	: Bounds(glm::vec3(0.0f), glm::vec3(0.0f))
	{
	}

	Bounds::Bounds(const glm::vec3& center, const glm::vec3& size)
	: m_center(center)
	{
		setSize(size);
	}

	bool Bounds::contains(const glm::vec3& point) const
	{
		return point.x >= m_min.x && point.y >= m_min.y && point.z >= m_min.z
				&& point.x <= m_max.x && point.y <= m_max.y && point.z <= m_max.z;
	}

	void Bounds::expand(const glm::vec3& amount)
	{
		setSize(m_size + amount);
	}

	bool Bounds::intersects(const Bounds& bounds) const
	{
		return !(bounds.m_min.x > m_max.x
						 || bounds.m_max.x < m_min.x
						 || bounds.m_min.y > m_max.y
						 || bounds.m_max.y < m_min.y
						 || bounds.m_min.z > m_max.z
						 || bounds.m_max.z < m_min.z
		);
	}

	void Bounds::setCenter(const glm::vec3& center)
	{
		m_center = center;
	}

	void Bounds::setSize(const glm::vec3& size)
	{
		m_size = size;
		m_extents = size / 2.0f;
		m_min = m_center - m_extents;
		m_max = m_center + m_extents;
	}

	void Bounds::setExtents(const glm::vec3& extents)
	{
		setSize(extents * 2.0f);
	}

	glm::vec3 Bounds::getCenter() const
	{
		return m_center;
	}

	glm::vec3 Bounds::getSize() const
	{
		return m_size;
	}

	glm::vec3 Bounds::getMin() const
	{
		return m_min;
	}

	glm::vec3 Bounds::getMax() const
	{
		return m_max;
	}
	
	glm::vec3 Bounds::getExtents() const
	{
		return m_extents;
	}

	Bounds Bounds::getBoundsOfTransformation(const glm::mat4& matrix) const
	{
		glm::vec3 min(std::numeric_limits<float>::min()), max(std::numeric_limits<float>::max());

		std::vector<glm::vec3> vertices {
				matrix * glm::vec4(m_center.x - m_extents.x, m_center.y + m_extents.y, m_center.z + m_extents.z, 1.0f), // LTF
				matrix * glm::vec4(m_center.x - m_extents.x, m_center.y + m_extents.y, m_center.z - m_extents.z, 1.0f), // LTB
				matrix * glm::vec4(m_center.x + m_extents.x, m_center.y + m_extents.y, m_center.z + m_extents.z, 1.0f), // RTF
				matrix * glm::vec4(m_center.x + m_extents.x, m_center.y + m_extents.y, m_center.z - m_extents.z, 1.0f), // RTB
				matrix * glm::vec4(m_center.x - m_extents.x, m_center.y - m_extents.y, m_center.z + m_extents.z, 1.0f), // LBF
				matrix * glm::vec4(m_center.x - m_extents.x, m_center.y - m_extents.y, m_center.z - m_extents.z, 1.0f), // LBB
				matrix * glm::vec4(m_center.x + m_extents.x, m_center.y - m_extents.y, m_center.z + m_extents.z, 1.0f), // RBF
				matrix * glm::vec4(m_center.x + m_extents.x, m_center.y - m_extents.y, m_center.z - m_extents.z, 1.0f)  // RBB
		};

		for (const auto& v : vertices)
		{
			if (v.x < min.x)
				min.x = v.x;

			if (v.y < min.y)
				min.y = v.y;

			if (v.z < min.z)
				min.z = v.z;

			if (v.x > max.x)
				max.x = v.x;

			if (v.y > max.y)
				max.y = v.y;

			if (v.z > max.z)
				max.z = v.z;
		}

		return Bounds(glm::vec3(matrix * glm::vec4(m_center, 1.0f)), max - min);
	}

	void Bounds::encompass(const glm::vec3& point)
	{
		throw std::runtime_error("Bounds::encompass not implemented!");
	}

	void Bounds::encompass(const Bounds& bounds)
	{
		throw std::runtime_error("Bounds::encompass not implemented!");
	}
}
