//
// Created by thors on 05.11.2019.
//

#ifndef AEYON3D_PLANE_H
#define AEYON3D_PLANE_H

#include <glm/glm.hpp>

namespace aeyon
{
  class Plane
  {
  public:
    glm::vec3 p, n;

    Plane() = default;
    Plane(const glm::vec3& p, const glm::vec3& n);

    float distance(const glm::vec3& point) const;
  };
}


#endif //AEYON3D_PLANE_H
