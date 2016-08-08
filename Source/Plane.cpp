#include "Plane.hpp"
#include <iostream>
#include "A5.hpp"
Plane::Plane(glm::vec3 vec1,glm::vec3 vec2, glm::vec3 vec3){
  v1 = vec1;
  v2 = vec2;
  v3 = vec3;
  normal=glm::normalize(glm::cross(v1-v2,v3-v2));
  dist = glm::dot(normal,v2);
}

float Plane::getDistance(glm::vec3 point)
{
  return dist - glm::dot(normal,point);
}
