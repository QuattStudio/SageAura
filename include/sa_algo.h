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



#define SA_Normalize_I(val, max)     ((val)/(max))









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




