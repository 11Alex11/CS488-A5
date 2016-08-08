#include "Sound.hpp"
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alut.h"

Sound::Sound(){
  looping=false;
  randPitch=true;
}

void Sound::load(std::string filename){
  buffer = alutCreateBufferFromFile(filename.c_str());
  alGenSources(1,&source);
  alSourcei(source,AL_BUFFER,buffer);
}

// Play a sound
void Sound::play(){
  // Randomize sound volume for uniqueness
  if(randPitch){
    float ran =((float) rand() / (RAND_MAX));
    ran = 0.1f + (float)(ran*(0.5f-0.1f));
    setPitch(ran);
  }
  alSourcePlay(source);
}


void Sound::loop(){
  ALenum state;
  if(randPitch){
    float ran =((float) rand() / (RAND_MAX));
    ran = 0.1f + (float)(ran*(0.5f-0.1f));
    setPitch(ran);
  }
  alGetSourcei(source, AL_SOURCE_STATE, &state);
  if(state!=AL_PLAYING){
    alSourcei(source,AL_LOOPING,AL_TRUE);
    play();
  }

}
void Sound::stopLoop(){
  alSourcei(source,AL_LOOPING,AL_FALSE);
}

// Actually sets gain , need to change these names
void Sound::setPitch(float val){
  alSourcef(source, AL_GAIN, val);
}

Sound::~Sound(){
  alDeleteBuffers(1, &buffer);
  alDeleteBuffers(1, &source);
}
