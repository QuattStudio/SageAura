#pragma once




#include "sa_platforms.h"
#include "sa_types.h"





SA_API SA_Vec2 SA_Vec2_Create(float x, float y);
SA_API SA_Vec2i SA_Vec2i_Create(int x, int y);



SA_API SA_Vec2 SA_Vec2_Add(SA_Vec2 vector1, SA_Vec2 vector2);
SA_API SA_Vec2i SA_Vec2i_Add(SA_Vec2i vector1, SA_Vec2i vector2);


SA_API SA_Vec2 SA_Vec2_Sub(SA_Vec2 vector1, SA_Vec2 vector2);
SA_API SA_Vec2i SA_Vec2i_Sub(SA_Vec2i vector1, SA_Vec2i vector2);




SA_API SA_Vec2 SA_Vec2_Scale(SA_Vec2 vector, float scale);
SA_API SA_Vec2i SA_Vec2i_Scale(SA_Vec2i vector, int scale);


SA_API float SA_Vec2_Length(SA_Vec2 vector);
SA_API float SA_Vec2i_Length(SA_Vec2i vector);


SA_API SA_Vec2 SA_Vec2_Normalize(SA_Vec2 vector);
SA_API SA_Vec2 SA_Vec2i_Normalize(SA_Vec2i vector);


SA_API float SA_Vec2_Distance(SA_Vec2 vector1, SA_Vec2 vector2);
SA_API float SA_Vec2i_Distance(SA_Vec2i vector1, SA_Vec2i vector2);


SA_API SA_Vec2 SA_Vec2_Lerp(SA_Vec2 vector1, SA_Vec2 vector2, float t);
SA_API SA_Vec2i SA_Vec2i_Lerp(SA_Vec2i vector1, SA_Vec2i vector2, float t);
