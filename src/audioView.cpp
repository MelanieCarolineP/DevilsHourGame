#include "audioView.h"

#include <iostream>

AudioView::AudioView() { gMusic = NULL; }

void AudioView::loadMedia() {
  gMusic = Mix_LoadMUS("../resource/audio/bg_music.mp3");
  if (gMusic == NULL) {
    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
  }
}

void AudioView::close() {
  // Free the music
  Mix_FreeMusic(gMusic);
  gMusic = NULL;

  // Quit SDL music subsystem
  Mix_Quit();
}

void AudioView::playMusic() { Mix_PlayMusic(gMusic, -1); }