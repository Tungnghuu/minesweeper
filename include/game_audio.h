#pragma once
#include <raylib.h>

extern Music music;
extern Sound sound0;
extern Sound sound1;
extern Sound sound2;
extern Sound sound3;
extern Sound soundFlag;

extern float masterVolume;
extern float musicVolume;
extern float sfxVolume;

void LoadSoundFX();
void UnloadSoundFX();