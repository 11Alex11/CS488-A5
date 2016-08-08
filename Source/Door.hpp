#pragma once
#include "Object.hpp"
#include "Sound.hpp"
class Door:public Object{
public:
  Door();
  virtual void clicked();
  ~Door();
private:
    Sound open;
};
