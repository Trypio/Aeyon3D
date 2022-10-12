#ifndef AEYON3D_FRUSTUM_HPP
#define AEYON3D_FRUSTUM_HPP

#include <glm/glm.hpp>
#include <array>
#include <vector>
#include "Plane.h"

namespace aeyon
{
    /**
     * Represents a camera's frustum.
     */
    class Frustum
    {
    private:
        enum { P_NEAR = 0, P_FAR, P_LEFT, P_RIGHT, P_TOP, P_BOTTOM };

        std::array<Plane, 6> m_planes;

    public:
        Frustum() = default;
        Frustum(const glm::vec3& cameraPos, const glm::vec3& cameraDir, const glm::vec3& cameraUp,
                float nearDist, float farDist, float fieldOfView, float aspect);

        /**
         * Checks if a given polygon intersects the frustum.
         * @param vertices The vertices of the polygon
         * @return true if there's an intersection, false if not
         */
        bool intersects(const std::vector<glm::vec3>& vertices) const;

        // TODO: Add optimized intersection checks (AABB, OOB, Polygon, ...)
    };
}

#endif //AEYON3D_FRUSTUM_HPP
