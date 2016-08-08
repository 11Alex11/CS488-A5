#pragma once
#include <glm/glm.hpp>
class Plane{
public:
  Plane(glm::vec3 v1,glm::vec3 v2, glm::vec3 v3);
  float getDistance(glm::vec3 point);
  glm::vec3 normal;
  float dist;
  glm::vec3 v1;
  glm::vec3 v2;
  glm::vec3 v3;
};
