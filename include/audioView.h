#ifndef _AUDIOVIEW_H_
#define _AUDIOVIEW_H_

#include <SDL_mixer.h>

class AudioView {
 private:
  /* data */
  Mix_Music *gMusic = NULL;

 public:
  AudioView();
  void loadMedia();
  void playMusic();
  void close();
};

#endif /* _AUDIOVIEW_H_ */