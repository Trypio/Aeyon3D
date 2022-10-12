#include "Graphics/Frustum.hpp"

namespace aeyon
{
    Frustum::Frustum(const glm::vec3& cameraPos, const glm::vec3& cameraDir, const glm::vec3& cameraUp, float nearDist,
                     float farDist, float fieldOfView, float aspect)
    {
        float nearHeight = 2.0f * glm::tan(glm::radians(fieldOfView / 2.0f)) * nearDist;
        float nearWidth = nearHeight * aspect;
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDir));

        glm::vec3 nearCenter = cameraPos + cameraDir * nearDist;
        glm::vec3 farCenter = cameraPos + cameraDir * farDist;
        glm::vec3 nearLeft = nearCenter - cameraRight * nearWidth / 2.0f;
        glm::vec3 nearRight = nearCenter + cameraRight * nearWidth / 2.0f;
        glm::vec3 nearTop = nearCenter + cameraUp * nearHeight / 2.0f;
        glm::vec3 nearBottom = nearCenter - cameraUp * nearHeight / 2.0f;

        m_planes[P_NEAR] = Plane(nearCenter, cameraDir);
        m_planes[P_FAR] = Plane(farCenter, -cameraDir);
        m_planes[P_LEFT] = Plane(nearLeft, glm::normalize(glm::cross(cameraUp, nearLeft - cameraPos)));
        m_planes[P_RIGHT] = Plane(nearRight, glm::normalize(glm::cross(nearRight - cameraPos, cameraUp)));
        m_planes[P_TOP] = Plane(nearTop, glm::normalize(glm::cross(cameraRight, nearTop - cameraPos)));
        m_planes[P_BOTTOM] = Plane(nearBottom, glm::normalize(glm::cross(nearBottom - cameraPos, cameraRight)));
    }

    bool Frustum::intersects(const std::vector<glm::vec3>& vertices) const
    {
        int out;
        for (int i = 0; i < 6; i++)
        {
            out = 0;
            for (const auto& v: vertices)
            {
                if (m_planes[i].distance(v) < 0.0f)
                    out++;
            }

            if (out == vertices.size())
                return false;
        }

        return true;
    }
}
