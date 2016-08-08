#include "Skybox.hpp"
#include "SOIL.h"
#include <iostream>
Skybox::Skybox(const char* front,const char* back, const char* top, const char* bottom,const char* left,const char* right){
    // load each image and copy into a side of the cube-map texture
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1,&tex);
  glBindTexture(GL_TEXTURE_CUBE_MAP,tex);


  loadSide ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
  loadSide ( GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
  loadSide (GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
  loadSide ( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
  loadSide ( GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
  loadSide (GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


  float points[] = {
  -10.0f,  10.0f, -10.0f,
  -10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,

  -10.0f, -10.0f,  10.0f,
  -10.0f, -10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f, -10.0f,
  -10.0f,  10.0f,  10.0f,
  -10.0f, -10.0f,  10.0f,

   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,

  -10.0f, -10.0f,  10.0f,
  -10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f, -10.0f,  10.0f,
  -10.0f, -10.0f,  10.0f,

  -10.0f,  10.0f, -10.0f,
   10.0f,  10.0f, -10.0f,
   10.0f,  10.0f,  10.0f,
   10.0f,  10.0f,  10.0f,
  -10.0f,  10.0f,  10.0f,
  -10.0f,  10.0f, -10.0f,

  -10.0f, -10.0f, -10.0f,
  -10.0f, -10.0f,  10.0f,
   10.0f, -10.0f, -10.0f,
   10.0f, -10.0f, -10.0f,
  -10.0f, -10.0f,  10.0f,
   10.0f, -10.0f,  10.0f
};

  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, 3 * 36 * sizeof (float), &points, GL_STATIC_DRAW);
  glBindBuffer (GL_ARRAY_BUFFER, 0);
  CHECK_GL_ERRORS;
}

// Draw the skybox using the skybox shader
void Skybox::draw(ShaderProgram& s){


  GLint posAttrib = s.getAttribLocation( "position" );

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP,tex);
  GLint cube = s.getUniformLocation("cubeMap");
  glUniform1i(cube,0);

  glEnableVertexAttribArray(posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

  glDrawArrays (GL_TRIANGLES, 0, 36);

  glBindBuffer(GL_ARRAY_BUFFER,0);




}
GLuint Skybox::getSkyboxTexture(){
  return tex;
}

// Load a side of the cube texture
void Skybox::loadSide(GLenum side,const char*file){
  int w,h;
  unsigned char* image = SOIL_load_image(file,&w,&h,0,SOIL_LOAD_RGBA);
  if(image==NULL){
    std::cerr << "Error loading " << file << std::endl;
    return;
  }
  glTexImage2D(side, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);


}
