#pragma once


#include "sa_platforms.h"
#include "core/sa_types.h"


// ────────────────────────────────────────────────
// Text / Font support (embedded in renderer)
// ────────────────────────────────────────────────

typedef struct SA_Font SA_Font;


extern SA_Font *SA_DefaultFont_I;














SA_API SA_Font* SA_LoadFont(const char* ttf_path, float pixel_size);

SA_API void SA_SetDefaultFont(SA_Font* font);


SA_API void SA_DrawText(const char* str, float x, float y, SA_Colori color);
SA_API void SA_DrawTextEx(SA_Font* font, const char* str, float x, float y, SA_Colori color);



SA_API void SA_UnLoadFont(SA_Font* font);