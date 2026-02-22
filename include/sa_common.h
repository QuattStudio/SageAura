/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once



#include <stdio.h>
#include <stdlib.h>


#include "sa_types.h"




#define SA_LOG_INFO(fmt, ...) \
    printf("[INFO] > " fmt "\n", ##__VA_ARGS__)


#define SA_LOG_WARN(fmt, ...) \
    printf("[WARN] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#define SA_LOG_ERROR(fmt, ...) \
    printf("[ERR] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#define SA_LOG_CRITICAL(fmt, ...) \
    printf("[CRITICAL] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); exit(1)






#ifndef SA_DISABLE_VERBOSE_LOGS_I


#define SA_LOGV_INFO(fmt, ...) \
    printf("[INFO-V] > " fmt "\n", ##__VA_ARGS__)


#define SA_LOGV_WARN(fmt, ...) \
    printf("[WARN-V] > {%s:%d} > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)


#endif

















#define SA_COLOR_MAX_OPACITY    (255)
#define SA_GL_VERSION_USED      (330)





#define SA_NOT  !
#define SA_OR   ||
#define SA_XOR  ^
#define SA_AND  &&






#define SA_MALLOC(type) ((type*)malloc(sizeof(type)))
#define SA_MALLOC_N(type, n) ((type*)malloc(sizeof(type * n)))



/* structs macros */

#define SA_RECT(x, y, width, height)    ((SA_Rect){(x), (y), (width), (height)})
#define SA_RECTF(x, y, width, height)    ((SA_RectF){(x), (y), (width), (height)})




/* colors */

#define SA_RGBA(r, g, b, a)     ((SA_Color){(r), (g), (b), (a)})
#define SA_RGB(r, g, b)     SA_RGBA((r), (g), (b), SA_COLOR_MAX_OPACITY)





#define SA_COLOR_RED                SA_RGB(255, 0, 0)
#define SA_COLOR_GREEN              SA_RGB(0, 255, 0)
#define SA_COLOR_BLUE               SA_RGB(0, 0, 255)
#define SA_COLOR_WHITE              SA_RGB(255, 255, 255)
#define SA_COLOR_BLACK              SA_RGB(0, 0, 0)

#define SA_COLOR_GRAY               SA_RGB(128, 128, 128)
#define SA_COLOR_GREY               SA_RGB(128, 128, 128)
#define SA_COLOR_GREY_COOL          SA_RGB(108, 117, 125)
#define SA_COLOR_GRAY_COOL          SA_RGB(108, 117, 125)

#define SA_COLOR_SLATE_DARK         SA_RGB(44, 62, 80)
#define SA_COLOR_CANDY_APPLE_RED    SA_RGB(255, 8, 0)
#define SA_COLOR_ELECTRIC_BLUE      SA_RGB(125, 249, 255)
#define SA_COLOR_NEON_GREEN         SA_RGB(57, 255, 20)
#define SA_COLOR_VIVID_VIOLET       SA_RGB(159, 0, 255)
#define SA_COLOR_GOLDEN_YELLOW      SA_RGB(255, 223, 0)
#define SA_COLOR_SAGE_GREEN         SA_RGB(188, 203, 184)
#define SA_COLOR_TERRACOTTA         SA_RGB(226, 114, 91)
#define SA_COLOR_MIDNIGHT_BLUE      SA_RGB(25, 25, 112)
#define SA_COLOR_OLIVE_DRAB         SA_RGB(107, 142, 35)
#define SA_COLOR_SAND_STONE         SA_RGB(194, 178, 128)
#define SA_COLOR_COTTON_CANDY       SA_RGB(255, 182, 193)
#define SA_COLOR_BABY_BLUE          SA_RGB(137, 207, 240)
#define SA_COLOR_MINT_CREAM         SA_RGB(245, 255, 250)
#define SA_COLOR_LAVENDER           SA_RGB(230, 230, 250)
#define SA_COLOR_PEACH_PUFF         SA_RGB(255, 218, 185)
#define SA_COLOR_MAUVE              SA_RGB(224, 176, 255)





#define SA_RED                      SA_COLOR_RED
#define SA_GREEN                    SA_COLOR_GREEN
#define SA_BLUE                     SA_COLOR_BLUE
#define SA_WHITE                    SA_COLOR_WHITE
#define SA_BLACK                    SA_COLOR_BLACK

#define SA_GRAY                     SA_COLOR_GRAY
#define SA_GREY                     SA_COLOR_GREY
#define SA_GREY_COOL                SA_COLOR_GREY_COOL
#define SA_GRAY_COOL                SA_COLOR_GRAY_COOL

#define SA_SLATE_DARK               SA_COLOR_SLATE_DARK
#define SA_CANDY_APPLE_RED          SA_COLOR_CANDY_APPLE_RED





#define SA_ELECTRIC_BLUE            SA_COLOR_ELECTRIC_BLUE
#define SA_NEON_GREEN               SA_COLOR_NEON_GREEN
#define SA_VIVID_VIOLET             SA_COLOR_VIVID_VIOLET
#define SA_GOLDEN_YELLOW            SA_COLOR_GOLDEN_YELLOW
#define SA_SAGE_GREEN               SA_COLOR_SAGE_GREEN
#define SA_TERRACOTTA               SA_COLOR_TERRACOTTA
#define SA_MIDNIGHT_BLUE            SA_COLOR_MIDNIGHT_BLUE
#define SA_OLIVE_DRAB               SA_COLOR_OLIVE_DRAB
#define SA_SAND_STONE               SA_COLOR_SAND_STONE
#define SA_COTTON_CANDY             SA_COLOR_COTTON_CANDY
#define SA_BABY_BLUE                SA_COLOR_BABY_BLUE
#define SA_MINT_CREAM               SA_COLOR_MINT_CREAM
#define SA_LAVENDER                 SA_COLOR_LAVENDER
#define SA_PEACH_PUFF               SA_COLOR_PEACH_PUFF
#define SA_MAUVE                    SA_COLOR_MAUVE













///////////////////// not now for future simplicity //////////////////////


// // color struct style

// typedef struct SA_COLOR {
    
//     SA_Color RED;
//     SA_Color GREEN;
//     SA_Color BLUE;
//     SA_Color WHITE;
//     SA_Color BLACK;
//     SA_Color GRAY;
//     SA_Color GREY;
//     SA_Color GREY_COOL; 
//     SA_Color GRAY_COOL;
//     SA_Color SLATE_DARK;
//     SA_Color CANDY_APPLE_RED;
//     SA_Color ELECTRIC_BLUE;
//     SA_Color NEON_GREEN;
//     SA_Color VIVID_VIOLET;
//     SA_Color GOLDEN_YELLOW;
//     SA_Color SAGE_GREEN;
//     SA_Color TERRACOTTA;
//     SA_Color MIDNIGHT_BLUE;
//     SA_Color OLIVE_DRAB;
//     SA_Color SAND_STONE;
//     SA_Color COTTON_CANDY;
//     SA_Color BABY_BLUE;
//     SA_Color MINT_CREAM;
//     SA_Color LAVENDER;
//     SA_Color PEACH_PUFF;
//     SA_Color MAUVE;               
// } SA_COLOR;