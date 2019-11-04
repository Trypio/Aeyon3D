//
//
//

#include <utility>
#include "BoxCollider.hpp"

namespace aeyon
{
	BoxCollider::BoxCollider()
	: BoxCollider(glm::vec3(0.0f), glm::vec3(1.0f))
	{
	}

	BoxCollider::BoxCollider(const glm::vec3& center, const glm::vec3& size)
			: m_center(center), m_size(size)
	{
	}

	glm::vec3 BoxCollider::getCenter() const
	{
		return m_center;
	}

	void BoxCollider::setCenter(glm::vec3 center)
	{
		m_center = center;
	}

	glm::vec3 BoxCollider::getSize() const
	{
		return m_size;
	}

	void BoxCollider::setSize(glm::vec3 size)
	{
		m_size = size;
	}
}
