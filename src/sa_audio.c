#include "sa_audio.h"

#include "sa_common.h"
#include "sa_types.h"



#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"


#include <stdlib.h>




typedef struct SA_Sound {
    ma_sound MAsound;
} SA_Sound;



static ma_engine SA_AudioEngine_I;




int SA_OpenAudioEngine_I()
{
    if (ma_engine_init(NULL, &SA_AudioEngine_I) != MA_SUCCESS) {
        SA_LOG_ERROR("Audio Initialization Failed!");
        return SA_FALSE;
    }

    return SA_TRUE;
}




void SA_CloseAudioEngine_I()
{
    ma_engine_uninit(&SA_AudioEngine_I);
}










SA_Sound* SA_SoundLoad(const char* path)
{
    SA_Sound* sound = SA_MALLOC(SA_Sound);
    if (SA_NOT sound) {
        SA_LOGV_WARN("Memory allocation failed while allocating sound for file: %s", path);
        goto SoundLoadingFailure;
    }

    int result =  ma_sound_init_from_file(
        &SA_AudioEngine_I,
        path,
        0,
        NULL,
        NULL,
        &sound->MAsound
    ) == MA_SUCCESS;


    if (SA_NOT result) {
        SA_LOGV_WARN("Not able to initialize miniaudio sound!");
        goto SoundLoadingFailure;
    }

    return sound;


SoundLoadingFailure:
    SA_LOG_WARN("Not able to load sound file: %s", path);
    return NULL;

}





void SA_SoundPlay(SA_Sound* sound)
{
    ma_sound_start(&sound->MAsound);
}



void SA_SoundPause(SA_Sound* sound)
{
    ma_sound_stop(&sound->MAsound);
}



void SA_SoundSetLoop(SA_Sound* sound, int loop)
{
    ma_sound_set_looping(&sound->MAsound, loop);
}



void SA_SoundSetVolume(SA_Sound* sound, float volume)
{
    ma_sound_set_volume(&sound->MAsound, volume);
}




void SA_SoundUnload(SA_Sound* sound)
{
    if (SA_NOT sound) {
        SA_LOG_WARN("No sound provided!");
        return;
    }


    ma_sound_uninit(&sound->MAsound);
}