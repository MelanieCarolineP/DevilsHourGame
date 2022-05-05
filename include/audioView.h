#ifndef _AUDIOVIEW_H_
#define _AUDIOVIEW_H_

#include <SDL_mixer.h>

#include <string>

class AudioView {
 private:
  // Music
  Mix_Music *gMusic = NULL;

  // Sounds effects
  Mix_Chunk *gInteract = NULL;
  Mix_Chunk *gDoor = NULL;

 public:
  AudioView();
  void loadMedia();
  void playMusic();
  void close();
  void playSound(std::string soundName);
};

#endif /* _AUDIOVIEW_H_ */