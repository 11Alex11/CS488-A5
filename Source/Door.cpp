#include "Door.hpp"
Door::Door():Object("Assets/Door/door.obj"){
  open.load("Assets/Sound/door.wav");
  animType=ANONE;
}
 void Door::clicked(){
  if(curFrame==0){
    animType=AFORWARD;
    open.play();
  }
  else if(curFrame==maxFrame-1){
      animType=ABACKWARD;
      open.play();
  }
}
Door::~Door(){

}
