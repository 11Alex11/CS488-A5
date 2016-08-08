#pragma once

#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"
#include <string>
class Sound{
public:
  Sound();
  ~Sound();
  void load(std::string filename);
  void play();
  void loop();
  void stopLoop();
  void setPitch(float val);
private:
  bool looping;
  bool randPitch;
  ALuint buffer;
  ALuint source;

};
