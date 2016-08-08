#include "Player.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Create player
Player::Player(float fov, float aspect, float near, float far):Object("Assets/WoodenLarry.obj"),aspect(aspect),near(near),far(far),fov(fov){
  walk.load("Assets/Sound/step.wav");
  perspective =glm::perspective(fov, aspect,near, far);
  speed = 10.0f;
  sensitivity = 0.1f;
  pitch = 0;
  yaw = 0;
  roll =0;

  movingX =movingZ= false;
  smoothX=smoothZ=accelX=accelZ=0;
  pos = glm::vec3(0,3,0);
  up=glm::vec3(0,1,0);
  front=glm::vec3(0,0,-1);
  right = glm::vec3(1,0,0);
  cameraMat=glm::lookAt(pos,pos+front,up);
}

void Player::moveCamera(char dir, float dTime){
  // Always Called before update camera
  // Smooths the movement
  if(dir=='z'){
    if(dTime==0){
      movingZ=false;
      smoothZ*=0.8;
      if(smoothZ<.3){
        smoothZ=0;
      }
      nextMoveZ*=smoothZ;
    }
    else{
      if(movingZ==false){
        accelZ=0.2;
      }
      accelZ*=1.2;
      if(accelZ>1){
        accelZ=1;
      }
      movingZ = true;
      nextMoveZ=front*speed*dTime*accelZ;
      smoothZ=1;
    }
  }
  if(dir=='x'){
    if(dTime==0){
      movingX=false;
      smoothX*=0.8;
      if(smoothX<.3){
        smoothX=0;
      }
      nextMoveX*=smoothX;
    }
    else{
      if(movingX==false){
        accelX=0.2;
      }
      accelX*=1.2;
      if(accelX>1){
        accelX=1;
      }
      movingX = true;
      nextMoveX=right*speed*dTime*accelX;
      smoothX=1;
    }
  }

  if(movingZ||movingX){
    walk.loop();
  }
  else{
    walk.stopLoop();
  }

}

void Player::rotateCamera(float xOffset,float yOffset){
  pitch+=-yOffset*sensitivity;
  yaw+=xOffset*sensitivity;
  if(pitch>75.0f){
    pitch = 75.0f;
  }
  else if(pitch<-75.0f){
    pitch = -75.0f;
  }

  // Recalculate front
  front.x = cos(glm::radians(pitch))*cos(glm::radians(yaw));
  front.z = cos(glm::radians(pitch))*sin(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front = glm::normalize(front);
  right = glm::normalize(glm::cross(front,glm::vec3(0,1,0)));
  up = glm::normalize(glm::cross(right,front));

}

void Player::updateCamera(){
  pos+=nextMoveZ + nextMoveX;
  cameraMat=glm::lookAt(pos,pos+front,up);
  trans=glm::translate(glm::mat4(),pos);
  trans = glm::rotate(trans,-glm::radians(yaw-90),glm::vec3(0,1,0));
  trans=glm::translate(trans,glm::vec3(0,-1.5,-0.25));
}

glm::mat4 Player::getCamera(){
return cameraMat;
}

glm::vec3 Player::getPos(){
return pos;
}
glm::vec3 Player::getDir(){
  return front;
}
glm::vec3 Player::getUp(){
  return up;
}
glm::vec3 Player::getRight(){
  return right;
}

glm::mat4 Player::getPerspective(){
return perspective;
}

float Player::getFar(){
return far;
}

float Player::getAspect(){
return aspect;
}

float Player::getFov(){
return fov;
}

float Player::getNear(){
return near;
}
Player::~Player(){

}
