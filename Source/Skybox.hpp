#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/GlErrorCheck.hpp"
class Skybox{
public:
  Skybox(const char* front,const char* back, const char* top, const char* bottom,const char* left,const char* right);
  void draw(ShaderProgram& s);
  GLuint getSkyboxTexture();
  GLuint tex;
private:
  void loadSide(GLenum side,const char*file);

  GLuint vbo;
  GLuint blockIbo;
};
