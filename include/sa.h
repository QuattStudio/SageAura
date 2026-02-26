/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once


#include "core/sa_colorl.h"

#include "core/sa_types.h"
#include "core/sa_common.h"

#include "sa_window.h"
#include "renderer/sa_renderer.h"
#include "sa_event.h"

#include "sa_text.h"
#include "sa_image.h"
#include "sa_audio.h"

#include "core/sa_math.h"






#define SA_MAIN()       int main(int argc, char **argv)









#ifdef SA_IMPORT_ALL



#define Start(flags)    SA_Start(flags)
#define OpenWindow(width, height, title)    SA_OpenWindow(width, height, title)
#define Play()      SA_Play()

#define BeginDrawing()      SA_BeginDrawing()
#define EndDrawing()        SA_EndDrawing()

#define CloseWindow()       SA_CloseWindow()



#define LoadTexture(file)       SA_LoadTexture(file)



#endif