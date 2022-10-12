#include "Plane.h"

namespace aeyon
{
  Plane::Plane(glm::vec3 p, glm::vec3 n) : p(std::move(p)), n(std::move(n))
  {
  }

  float Plane::distance(const glm::vec3& point) const
  {
    return -glm::dot(n, p) + glm::dot(n, point);
  }
}