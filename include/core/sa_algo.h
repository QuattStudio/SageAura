/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/



#pragma once





#include "sa_types.h"



#define SA_ALGO_API_I    static inline
#define SA_ALGO_MAX_OPACITY_I     (255)




#define SA_Normalize_I(val, max) ((val) / (float)(max))









SA_ALGO_API_I
SA_Color SA_NormalizeColor(SA_Colori color)
{
    SA_Color colorf;

    colorf.r = SA_Normalize_I(color.r, SA_ALGO_MAX_OPACITY_I);
    colorf.g = SA_Normalize_I(color.g, SA_ALGO_MAX_OPACITY_I);
    colorf.b = SA_Normalize_I(color.b, SA_ALGO_MAX_OPACITY_I);
    colorf.a = 1.0f;

    return colorf;
}





SA_ALGO_API_I
SA_Color SA_NormalizeColorEx(SA_Colori color)
{
    SA_Color colorf;

    colorf.r = SA_Normalize_I(color.r, SA_ALGO_MAX_OPACITY_I);
    colorf.g = SA_Normalize_I(color.g, SA_ALGO_MAX_OPACITY_I);
    colorf.b = SA_Normalize_I(color.b, SA_ALGO_MAX_OPACITY_I);
    colorf.a = SA_Normalize_I(color.a, SA_ALGO_MAX_OPACITY_I);


    return colorf;
}







// move from a to b by t (t = 0.0 to 1.0)
// t=0 returns a, t=1 returns b, t=0.5 returns middle
SA_ALGO_API_I float SA_Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}



// keep value between min and max
SA_ALGO_API_I float SA_Clamp(float val, float min, float max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}



// remap value from one range to another
// example: SA_Map(0.5, 0,1, 0,100) = 50
// example: SA_Map(128, 0,255, 0,1) = 0.5  (normalize)
SA_ALGO_API_I float SA_Map(float val, float a, float b, float c, float d) {
    return c + (val - a) / (b - a) * (d - c);
}





// returns 1 if rects overlap, 0 if not
SA_ALGO_API_I int SA_CheckCollision(SA_Rect a, SA_Rect b) {
    return a.x < b.x + b.width &&
           a.x + a.width > b.x &&
           a.y < b.y + b.height &&
           a.y + a.height > b.y;
}



SA_ALGO_API_I int SA_CheckCollisionInt(SA_Recti a, SA_Recti b) {
    return a.x < b.x + b.width &&
           a.x + a.width > b.x &&
           a.y < b.y + b.height &&
           a.y + a.height > b.y;
}



// returns 1 if point is inside rect
SA_ALGO_API_I int SA_CheckCollisionPoint(float px, float py, SA_Rect r) {
    return px >= r.x && px <= r.x + r.width &&
           py >= r.y && py <= r.y + r.height;
}



// returns 1 if point is inside rect
SA_ALGO_API_I int SA_CheckCollisionPointInt(float px, float py, SA_Recti r) {
    return px >= r.x && px <= r.x + r.width &&
           py >= r.y && py <= r.y + r.height;
}




// returns 1 if rect a is fully inside rect b
SA_ALGO_API_I int SA_RectContains(SA_Rect outer, SA_Rect inner) {
    return inner.x >= outer.x &&
           inner.y >= outer.y &&
           inner.x + inner.width <= outer.x + outer.width &&
           inner.y + inner.height <= outer.y + outer.height;
}






// returns 1 if rect a is fully inside rect b
SA_ALGO_API_I int SA_RectContainsInt(SA_Recti outer, SA_Recti inner) {
    return inner.x >= outer.x &&
           inner.y >= outer.y &&
           inner.x + inner.width <= outer.x + outer.width &&
           inner.y + inner.height <= outer.y + outer.height;
}