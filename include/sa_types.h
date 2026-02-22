/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once



#include <stdint.h>


/* SageAura int & uint types */


// unsigned int (unsigned int)
typedef unsigned int    SA_Uint;

// unsigned int-8 (unsigned char)
typedef uint8_t     SA_Uint8;

// unsigned int-16 (unsigned short)
typedef uint16_t    SA_Uint16;

// unsigned int-32 (unsigned int)
typedef uint32_t    SA_Uint32;

// unsigned int-64 (unsigned long long)
typedef uint64_t    SA_Uint64;



// signed int-8 (signed char)
typedef int8_t      SA_Int8;

// signed int-16 (signed short)
typedef int16_t     SA_Int16;

// signed int-32 (signed int)
typedef int32_t     SA_Int32;

// signed int-64 (signed long long)
typedef int64_t     SA_Int64;














/* 
    SageAura bools contains:

    SA_YES, SA_TRUE,
    SA_NO, SA_FALSE
*/
typedef enum {
    SA_NO = 0,
    SA_FALSE = 0,
    SA_TRUE = 1,
    SA_YES = 1, 
} SA_Bool;



/*
    SageAura Color is a struct (of int)
    contains:

    int r, g, b, a;
*/
typedef struct SA_Color {
    int r;
    int g;
    int b;
    int a;
} SA_Color;





/*
    SageAura ColorF is a float struct
    contains:

    float r, g, b, a;
*/
typedef struct SA_ColorF {
    float r;
    float g;
    float b;
    float a;
} SA_ColorF;










/*
    SageAura Rect is a struct (of int)
    contains:

    int r, g, b, a;
*/
typedef struct SA_Rect 
{
    int x;
    int y;
    int width;
    int height;
} SA_Rect;






/*
    SageAura RectF is a float struct
    contains:

    float r, g, b, a;
*/
typedef struct SA_RectF 
{
    float x;
    float y;
    float width;
    float height;
} SA_RectF;





/*
    SageAura Vec2 is a float struct
    contains:

    float x, y;
*/
typedef struct SA_Vec2 {
    float x;
    float y;
} SA_Vec2;





/**
 * Represents a 2D camera used to view world space.
 *
 * Controls what portion of the world is visible
 * and how it is transformed on screen.
 */
typedef struct SA_Camera2D
{
    SA_Vec2 position;   ///< camera position in world space
    float zoom;         ///< zoom factor (1.0 = default)
    float rotation;     ///< rotation angle in degrees
} SA_Camera2D;









/**
 * Represents a simple 2D physics body.
 *
 * Used for movement, gravity, and collision response.
 */
typedef struct SA_Body2D
{
    SA_Vec2 velocity;      ///< current movement velocity
    SA_Vec2 acceleration;  ///< acceleration applied each frame
    float mass;            ///< mass affecting physics response
    int grounded;          ///< non-zero if touching ground
} SA_Body2D;