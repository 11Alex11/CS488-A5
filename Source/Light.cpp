#include <iostream>

#include <glm/ext.hpp>

#include "Light.hpp"



Light::Light(float t,glm::vec3 pos,glm::vec3 color,int shadowsize):type(t)
{
  enabled = true;
  colour = color;
  position = pos;
  if(type==0){
    attenuation = glm::vec3(1,0,0);
  }
  else{
    attenuation = glm::vec3(1,.01,0);
  }
  shadowmapSize=shadowsize;
  glGenTextures(1, &shadowMap);

  	glBindTexture(GL_TEXTURE_2D, shadowMap);
  	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,shadowmapSize, shadowmapSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glGenTextures(1, &shadowCubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadowCubeMap);
    for (uint i = 0 ; i < 6 ; i++) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                           shadowmapSize, shadowmapSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);



}
