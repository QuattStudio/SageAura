#pragma once




#include "sa_platforms.h"


typedef struct SA_Sound SA_Sound;




int SA_OpenAudioEngine_I();

void SA_CloseAudioEngine_I();



SA_API
SA_Sound* SA_SoundLoad(const char* path);

SA_API
void SA_SoundPlay(SA_Sound* sound);

SA_API
void SA_SoundPause(SA_Sound* sound);


SA_API
void SA_SoundSetLoop(SA_Sound* sound, int loop);

SA_API
void SA_SoundSetVolume(SA_Sound* sound, float volume);

SA_API
void SA_SoundUnload(SA_Sound* sound);