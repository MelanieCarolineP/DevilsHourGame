#include "audioView.h"

#include <iostream>

AudioView::AudioView() { gMusic = NULL; }

void AudioView::loadMedia() {
  // Load music
  gMusic = Mix_LoadMUS("../resource/audio/bg_music.mp3");
  if (gMusic == NULL) {
    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
  }

  // Load sound effects
  gInteract = Mix_LoadWAV("../resource/audio/interact.wav");
  if (gInteract == NULL) {
    printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
  }

  gDoor = Mix_LoadWAV("../resource/audio/open_door.wav");
  if (gDoor == NULL) {
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

void AudioView::playSound(std::string soundName) {
  if (soundName == "interact") {
    Mix_PlayChannel(-1, gInteract, 0);
  } else if (soundName == "door") {
    Mix_PlayChannel(-1, gDoor, 0);
  } else {
    Mix_PlayChannel(-1, gInteract, 0);
  }
}

void AudioView::playMusic() { Mix_PlayMusic(gMusic, -1); }