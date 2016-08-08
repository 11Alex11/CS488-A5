#pragma once

#include "Object.hpp"
#include "Sound.hpp"
class Player: public Object{
public:
  Player(float fov, float aspect, float near, float far);
  ~Player();
  void moveCamera(char dir,float dTime);
  void updateCamera();
  void rotateCamera(float xOffset,float yOffset);
  glm::mat4 getCamera();
  glm::mat4 getPerspective();
  glm::vec3 getPos();

  glm::vec3 getDir();
  glm::vec3 getUp();
  glm::vec3 getRight();


  float getFar();
  float getNear();
  float getAspect();
  float getFov();
  float yaw;
  float pitch;
private:
  glm::vec3 pos;
  glm::vec3 up;
  glm::vec3 front;
  glm::vec3 right;
  glm::mat4 cameraMat;
  glm::mat4 perspective;
  float aspect;
  float far;
  float near;
  float fov;
  glm::vec3 nextMoveZ;
  glm::vec3 nextMoveX;
  float smoothX,smoothZ,accelX,accelZ;
  bool movingX,movingZ;

  float roll;
  float speed;
  float sensitivity;

  Sound walk;
};
