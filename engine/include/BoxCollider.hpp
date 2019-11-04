//
//
//

#ifndef AEYON3D_BOXCOLLIDER_HPP
#define AEYON3D_BOXCOLLIDER_HPP

#include "Collider.hpp"
#include <glm/glm.hpp>

namespace aeyon
{
	class BoxCollider : public Collider
	{
	private:
		glm::vec3 m_center;
		glm::vec3 m_size;

	public:
		BoxCollider();
		BoxCollider(const glm::vec3& center, const glm::vec3& size);

		glm::vec3 getCenter() const;
		void setCenter(glm::vec3 center);

		glm::vec3 getSize() const;
		void setSize(glm::vec3 size);
	};
}


#endif
