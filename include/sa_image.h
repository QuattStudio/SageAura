#pragma once

#include "core/sa_types.h"
#include "sa_platforms.h"




typedef struct SA_Texture SA_Texture;



// #include "glh.h"



SA_API SA_Texture* SA_LoadTexture(const char* filepath);



// u0,v0 = top-left texcoord, u1,v1 = bottom-right texcoord
SA_API void SA_DrawTexture(SA_Texture* tex, SA_Rect* rect);
// SA_API void SA_DrawTextureEx(SA_Texture* tex, int x, int y, int w, int h, int rotation, int scaleX, int scaleY);


SA_API void SA_UnloadTexture(SA_Texture* texture);




