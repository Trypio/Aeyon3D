//
//
//

#ifndef AEYON3D_BOUNDS_HPP
#define AEYON3D_BOUNDS_HPP

#include <glm/glm.hpp>

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
		Bounds();
		Bounds(const glm::vec3& center, const glm::vec3& size);

		bool contains(const glm::vec3& point) const;
		void expand(const glm::vec3& amount);
		bool intersects(const Bounds& bounds) const;
		void encompass(const glm::vec3& point);
		void encompass(const Bounds& bounds);
		Bounds getBoundsOfTransformation(const glm::mat4& matrix) const;

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
