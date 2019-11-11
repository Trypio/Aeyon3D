//
//
//

#ifndef AEYON3D_BOUNDS_HPP
#define AEYON3D_BOUNDS_HPP

#include <glm/glm.hpp>
#include <vector>

namespace aeyon
{
	class Bounds
	{
	private:
		glm::vec3 m_center;
		glm::vec3 m_size;
		glm::vec3 m_extents;
		glm::vec3 m_min, m_max;

	public:
	  static Bounds fromPoints(const std::vector<glm::vec3>& points);

		Bounds();
		Bounds(const glm::vec3& center, const glm::vec3& size);

		bool contains(const glm::vec3& point) const;
		bool contains(const Bounds& bounds) const;

		bool intersects(const Bounds& bounds) const;

		void expand(const glm::vec3& amount);
		void encompass(const glm::vec3& point);
		void encompass(const Bounds& bounds);

		std::vector<glm::vec3> getVertices() const;

		glm::vec3 getMin() const;
		glm::vec3 getMax() const;

		void setCenter(const glm::vec3& center);
		void setSize(const glm::vec3& size);
		void setExtents(const glm::vec3& extents);

		glm::vec3 getCenter() const;
		glm::vec3 getSize() const;
		glm::vec3 getExtents() const;
	};
}

#endif //AEYON3D_BOUNDS_HPP
