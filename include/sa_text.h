#pragma once


#include "sa_platforms.h"
#include "sa_types.h"


// ────────────────────────────────────────────────
// Text / Font support (embedded in renderer)
// ────────────────────────────────────────────────

typedef struct SA_Font SA_Font;


















SA_API SA_Font* SA_CreateFont(const char* ttf_path, float pixel_size);



SA_API void SA_DrawText(SA_Font* font, const char* str, float x, float y, SA_Colori color);



SA_API void SA_UnLoadFont(SA_Font* font);