#pragma once

#include "sa_types.h"
#include "sa_platforms.h"




typedef struct SA_Texture SA_Texture;



// #include "glh.h"



SA_API SA_Texture* SA_LoadTexture(const char* filepath);



// u0,v0 = top-left texcoord, u1,v1 = bottom-right texcoord
SA_API void SA_DrawTexture(SA_Texture* tex, int x, int y, int w, int h);
SA_API void SA_UnLoadTexture(SA_Texture* texture);




