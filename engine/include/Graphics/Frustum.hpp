//
//
//
#ifndef AEYON3D_FRUSTUM_HPP
#define AEYON3D_FRUSTUM_HPP

#include <glm/glm.hpp>
#include <array>
#include <vector>
#include "Plane.h"

namespace aeyon
{
	struct Frustum
	{
		enum { P_NEAR = 0, P_FAR, P_LEFT, P_RIGHT, P_TOP, P_BOTTOM };

  private:
		std::array<Plane, 6> planes;

	public:
		Frustum() = default;

		Frustum(const glm::vec3& cameraPos, const glm::vec3& cameraDir, const glm::vec3& cameraUp,
				    float nearDist, float farDist, float fieldOfView, float aspect);

		bool contains(const glm::vec3& point) const;
		bool intersects(const std::vector<glm::vec3>& vertices) const;
	};
}

#endif //AEYON3D_FRUSTUM_HPP
