//
// Created by thors on 05.11.2019.
//

#include "Plane.h"

namespace aeyon
{
  Plane::Plane(const glm::vec3& p, const glm::vec3& n) : p(p), n(n)
  {
  }

  float Plane::distance(const glm::vec3& point) const
  {
    return -glm::dot(n, p) + glm::dot(n, point);
  }
}