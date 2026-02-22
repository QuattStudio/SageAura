/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/



#pragma once





#include "sa_types.h"
#include "sa_common.h"



#define SA_ALGO_API_I    static inline




#define SA_Normalize_I(val, max)     ((val)/(max))









SA_ALGO_API_I
SA_ColorF SA_NormalizeColor(int r, int g, int b)
{
    SA_ColorF colorf;

    colorf.r = SA_Normalize_I(r, SA_COLOR_MAX_OPACITY);
    colorf.g = SA_Normalize_I(g, SA_COLOR_MAX_OPACITY);
    colorf.b = SA_Normalize_I(b, SA_COLOR_MAX_OPACITY);
    colorf.a = 1.0f;

    return colorf;
}





SA_ALGO_API_I
SA_ColorF SA_NormalizeColorEx(int r, int g, int b, int a)
{
    SA_ColorF colorf;

    colorf.r = SA_Normalize_I(r, SA_COLOR_MAX_OPACITY);
    colorf.g = SA_Normalize_I(g, SA_COLOR_MAX_OPACITY);
    colorf.b = SA_Normalize_I(b, SA_COLOR_MAX_OPACITY);
    colorf.a = SA_Normalize_I(a, SA_COLOR_MAX_OPACITY);


    return colorf;
}




