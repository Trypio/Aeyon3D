//
//
//

#ifndef AEYON3D_FRUSTUM_HPP
#define AEYON3D_FRUSTUM_HPP

#include <glm/glm.hpp>
#include <array>

namespace aeyon
{
	struct Frustum
	{
		struct Plane
		{
			glm::vec3 p, n;

			Plane() : Plane(glm::vec3(0.0f), glm::vec3(0.0f))
			{
			}

			Plane(const glm::vec3& p, const glm::vec3& n) : p(p), n(n)
			{
			}

			float distance(const glm::vec3& point) const
			{
				return -glm::dot(n, p) + glm::dot(n, point);
			}
		};

		enum { P_NEAR = 0, P_FAR, P_LEFT, P_RIGHT, P_TOP, P_BOTTOM };
		std::array<Plane, 6> planes;

		Frustum() {}; // TODO

		Frustum(const glm::vec3& cameraPos, const glm::vec3& cameraDir, const glm::vec3& cameraUp,
				    float nearDist, float farDist, float fieldOfView, float aspect)
		{
			float nearHeight = 2.0f * glm::tan(glm::radians(fieldOfView / 2.0f)) * nearDist;
			float nearWidth = nearHeight * aspect;

			glm::vec3 nearCenter = cameraPos + cameraDir * nearDist;
			glm::vec3 farCenter = cameraPos + cameraDir * farDist;
			glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDir));

			planes[P_NEAR] = Plane(nearCenter, cameraDir);
			planes[P_FAR] = Plane(farCenter, -cameraDir);
			planes[P_LEFT] = Plane(nearCenter - cameraRight * nearWidth / 2.0f, glm::normalize(glm::cross(cameraUp, (nearCenter - cameraRight * nearWidth / 2.0f) - cameraPos)));
			planes[P_RIGHT] = Plane(nearCenter + cameraRight * nearWidth / 2.0f, glm::normalize(glm::cross((nearCenter + cameraRight * nearWidth / 2.0f) - cameraPos, cameraUp)));
			planes[P_TOP] = Plane(nearCenter + cameraUp * nearHeight / 2.0f, glm::normalize(glm::cross(cameraRight, (nearCenter + cameraUp * nearHeight / 2.0f) - cameraPos)));
			planes[P_BOTTOM] = Plane(nearCenter - cameraUp * nearHeight / 2.0f, glm::normalize(glm::cross((nearCenter - cameraUp * nearHeight / 2.0f) - cameraPos, cameraRight)));
		}

		bool testPoint(const glm::vec3& point) const
		{
			for (int i = 0; i < 6; i++)
				if (planes[i].distance(point) < 0.0f)
					return false;

			return true;
		}

		bool testBox(const std::vector<glm::vec3>& vertices) const
		{
			int in;

			for (int i = 0; i < 6; i++)
			{
				in = 0;
				for (int v = 0; v < 8; v++)
				{
					if (planes[i].distance(vertices[v]) >= 0.0f)
						in++;
				}

				if (!in)
					return false;
			}

			return true;
		}

	};
}

#endif //AEYON3D_FRUSTUM_HPP
