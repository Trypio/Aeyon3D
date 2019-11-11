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

	Bounds Bounds::fromPoints(const std::vector<glm::vec3>& points)
  {
    glm::vec3 min(std::numeric_limits<float>::max()), max(std::numeric_limits<float>::min());

    for (const auto& p : points)
    {
      min.x = std::min(min.x, p.x);
      min.y = std::min(min.y, p.y);
      min.z = std::min(min.z, p.z);
      max.x = std::max(max.x, p.x);
      max.y = std::max(max.y, p.y);
      max.z = std::max(max.z, p.z);
    }

    return Bounds(max - (max - min) / 2.0f, max - min);
  }

	bool Bounds::contains(const glm::vec3& point) const
	{
		return point.x >= m_min.x && point.y >= m_min.y && point.z >= m_min.z
				&& point.x <= m_max.x && point.y <= m_max.y && point.z <= m_max.z;
	}

	bool Bounds::contains(const Bounds& bounds) const
	{
		return m_min.x <= bounds.m_min.x && m_min.y <= bounds.m_min.y && m_min.z <= bounds.m_min.z
		&& m_max.x >= bounds.m_max.x && m_max.y >= bounds.m_max.y && m_max.z >= bounds.m_max.z;
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

	std::vector<glm::vec3> Bounds::getVertices() const
	{
		// LBF, LTF, RTF, RBF, LBB, LTB, RTB, RBB
		return {
				{ m_center.x - m_extents.x, m_center.y - m_extents.y, m_center.z - m_extents.z },
				{ m_center.x - m_extents.x, m_center.y + m_extents.y, m_center.z - m_extents.z },
				{ m_center.x + m_extents.x, m_center.y + m_extents.y, m_center.z - m_extents.z },
				{ m_center.x + m_extents.x, m_center.y - m_extents.y, m_center.z - m_extents.z },
				{ m_center.x - m_extents.x, m_center.y - m_extents.y, m_center.z + m_extents.z },
				{ m_center.x - m_extents.x, m_center.y + m_extents.y, m_center.z + m_extents.z },
				{ m_center.x + m_extents.x, m_center.y + m_extents.y, m_center.z + m_extents.z },
				{ m_center.x + m_extents.x, m_center.y - m_extents.y, m_center.z + m_extents.z }
		};
	}

	void Bounds::setCenter(const glm::vec3& center)
	{
		m_center = center;
		m_min = m_center - m_extents;
		m_max = m_center + m_extents;
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

	void Bounds::encompass(const glm::vec3& point)
	{
		float diff = point.x - m_center.x;
		if (glm::abs(diff) >= m_extents.x)
		{
			setCenter(m_center + glm::vec3(glm::sign(diff) * (glm::abs(diff) - m_extents.x) / 2.0f, 0.0f, 0.0f));
			setSize(glm::vec3(glm::abs(diff) + m_extents.x, m_size.y, m_size.z));
		}

		diff = point.y - m_center.y;
		if (glm::abs(diff) >= m_extents.y)
		{
			setCenter(m_center + glm::vec3(0.0f, glm::sign(diff) * (glm::abs(diff) - m_extents.y) / 2.0f, 0.0f));
			setSize( glm::vec3(m_size.x, glm::abs(diff) + m_extents.y, m_size.z));
		}

		diff = point.z - m_center.z;
		if (glm::abs(diff) >= m_extents.z)
		{
			setCenter(m_center + glm::vec3(0.0f, 0.0f, glm::sign(diff) * (glm::abs(diff) - m_extents.z) / 2.0f));
			setSize(glm::vec3(m_size.x, m_size.y, glm::abs(diff) + m_extents.z));
		}
	}

	void Bounds::encompass(const Bounds& bounds)
	{
		for (const auto& p : bounds.getVertices())
		{
			encompass(p);
		}
	}
}
