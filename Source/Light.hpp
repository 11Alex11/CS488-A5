#pragma once

#include <iosfwd>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cs488-framework/OpenGLImport.hpp"
// Represents a simple point light.
struct Light {
  Light(float type,glm::vec3 pos,glm::vec3 color,int shadowsize=2048);

  GLuint shadowMap;
  GLuint shadowCubeMap;
  int shadowmapSize;
  bool enabled;
  glm::mat4 depthMV;
  glm::vec3 colour;
  glm::vec3 position;
  glm::vec3 attenuation;
  float type;
};
