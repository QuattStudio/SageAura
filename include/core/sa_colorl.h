/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/


#pragma once


#include "sa_types.h"
#include "sa_algo.h"

#include <stdio.h>
#include <string.h>




#define SA_COLOR_API    static inline




SA_COLOR_API
SA_Colori SA_ColorFromHex(const char *hex)
{
    SA_Colori color = {0,0,0,255};
    unsigned int value = 0;

    if (hex[0] == '#') hex++;

    sscanf(hex, "%x", &value);

    if (strlen(hex) <= 6) {
        color.r = (value >> 16) & 0xFF;
        color.g = (value >> 8)  & 0xFF;
        color.b = value & 0xFF;
    } else {
        color.r = (value >> 24) & 0xFF;
        color.g = (value >> 16) & 0xFF;
        color.b = (value >> 8)  & 0xFF;
        color.a = value & 0xFF;
    }

    return color;
}

/* colors */

#define SA_RGBA(r, g, b, a)     ((SA_Colori){(r), (g), (b), (a)})
#define SA_RGB(r, g, b)         SA_RGBA((r), (g), (b), SA_COLOR_MAX_OPACITY)




// basic colors

#define SA_COLOR_RED                SA_RGB(255, 0, 0)
#define SA_COLOR_BLUE               SA_RGB(0, 0, 255)
#define SA_COLOR_WHITE              SA_RGB(255, 255, 255)
#define SA_COLOR_BLACK              SA_RGB(0, 0, 0)
#define SA_COLOR_GREEN              SA_RGB(0, 128, 0)

// sage colors

#define SA_COLOR_SAGE_GREEN         SA_RGB(188, 203, 184)

// neon

#define SA_COLOR_NEON_GREEN         SA_RGB(57, 255, 20)

// other colors


#define SA_COLOR_GRAY               SA_RGB(128, 128, 128)
#define SA_COLOR_GREY               SA_RGB(128, 128, 128)
#define SA_COLOR_GREY_COOL          SA_RGB(108, 117, 125)
#define SA_COLOR_GRAY_COOL          SA_RGB(108, 117, 125)
#define SA_COLOR_DARK_GREY          SA_RGB(169, 169, 169)
#define SA_COLOR_DARK_GRAY          SA_RGB(169, 169, 169)


#define SA_COLOR_LIME               SA_RGB(0, 255, 0)

#define SA_COLOR_ORANGE             SA_RGB(255, 165, 0, 255)
#define SA_COLOR_SLATE_DARK         SA_RGB(44, 62, 80)
#define SA_COLOR_CANDY_APPLE_RED    SA_RGB(255, 8, 0)
#define SA_COLOR_ELECTRIC_BLUE      SA_RGB(125, 249, 255)
#define SA_COLOR_VIVID_VIOLET       SA_RGB(159, 0, 255)
#define SA_COLOR_GOLDEN_YELLOW      SA_RGB(255, 223, 0)
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

#define SA_COLOR_AQUA               SA_RGB(0, 255, 255)
#define SA_COLOR_CORN_FLOWER_BLUE   SA_RGB(100, 149, 237)
#define SA_COLOR_ALICE_BLUE         SA_RGB(240, 248, 255)
#define SA_COLOR_ANTIQUE_WHITE      SA_RGB(250, 235, 215)
#define SA_COLOR_AQUA_MARINE        SA_RGB(127, 255, 212)
#define SA_COLOR_AZURE              SA_RGB(240, 255, 255)
#define SA_COLOR_BEIGE              SA_RGB(245, 245, 220)
#define SA_COLOR_BISQUE             SA_RGB(255, 228, 196)
#define SA_COLOR_BLANCHEDALMOND     SA_RGB(255, 235, 205)
#define SA_COLOR_BLUEVIOLET         SA_RGB(138, 43, 226)
#define SA_COLOR_BROWN              SA_RGB(165, 42, 42)
#define SA_COLOR_BURLYWOOD          SA_RGB(222, 184, 135)
#define SA_COLOR_CADET_BLUE         SA_RGB(95, 158, 160)
#define SA_COLOR_CHARTREUSE         SA_RGB(127, 255, 0)
#define SA_COLOR_CHOCOLATE          SA_RGB(210, 105, 30)
#define SA_COLOR_CORAL              SA_RGB(255, 127, 80)
#define SA_COLOR_CORNSILK           SA_RGB(255, 248, 220)
#define SA_COLOR_CRIMSON            SA_RGB(220, 20, 60)
#define SA_COLOR_CYAN               SA_RGB(0, 255, 255)
#define SA_COLOR_DARKBLUE           SA_RGB(0, 0, 139)
#define SA_COLOR_DARKCYAN           SA_RGB(0, 139, 139)
#define SA_COLOR_DARKGOLDENROD      SA_RGB(184, 134, 11)
#define SA_COLOR_TEAL               SA_RGB(0, 128, 128)
#define SA_COLOR_VIOLET             SA_RGB(238, 130, 238)
#define SA_COLOR_WHITESMOKE         SA_RGB(245, 245, 245)
#define SA_COLOR_YELLOW             SA_RGB(255, 255, 0)
#define SA_COLOR_TAN                SA_RGB(210, 180, 140)
#define SA_COLOR_SNOW               SA_RGB(255, 250, 250)
#define SA_COLOR_DEEPSKYBLUE        SA_RGB(0, 191, 255)
#define SA_COLOR_SILVER             SA_RGB(192, 192, 192)
#define SA_COLOR_ROYALBLUE          SA_RGB(65, 105, 225)
#define SA_COLOR_INDIGO             SA_RGB(75, 0, 130)
#define SA_COLOR_MAROON             SA_RGB(128, 0, 0)
#define SA_COLOR_NAVY               SA_RGB(0, 0, 128)






#define SA_RED                      SA_COLOR_RED
#define SA_LIME                     SA_COLOR_LIME
#define SA_BLUE                     SA_COLOR_BLUE
#define SA_WHITE                    SA_COLOR_WHITE
#define SA_BLACK                    SA_COLOR_BLACK
#define SA_GREEN                    SA_COLOR_GREEN
#define SA_ORANGE                   SA_COLOR_ORANGE

#define SA_GRAY                     SA_COLOR_GRAY
#define SA_GREY                     SA_COLOR_GREY // both are same just english difference use whatever you want
#define SA_GREY_COOL                SA_COLOR_GREY_COOL
#define SA_GRAY_COOL                SA_COLOR_GRAY_COOL
#define SA_DARK_GREY                SA_COLOR_DARK_GREY
#define SA_DARK_GRAY                SA_COLOR_DARK_GRAY



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






#define SA_AQUA                     SA_COLOR_AQUA
#define SA_CORN_FLOWER_BLUE         SA_COLOR_CORN_FLOWER_BLUE
#define SA_ALICE_BLUE               SA_COLOR_ALICE_BLUE
#define SA_ANTIQUE_WHITE            SA_COLOR_ANTIQUE_WHITE
#define SA_AQUA_MARINE              SA_COLOR_AQUA_MARINE
#define SA_AZURE                    SA_COLOR_AZURE
#define SA_BEIGE                    SA_COLOR_BEIGE
#define SA_BISQUE                   SA_COLOR_BISQUE
#define SA_BLANCHEDALMOND           SA_COLOR_BLANCHEDALMOND
#define SA_BLUEVIOLET               SA_COLOR_BLUEVIOLET
#define SA_BROWN                    SA_COLOR_BROWN
#define SA_BURLYWOOD                SA_COLOR_BURLYWOOD
#define SA_CADET_BLUE               SA_COLOR_CADET_BLUE
#define SA_CHARTREUSE               SA_COLOR_CHARTREUSE
#define SA_CHOCOLATE                SA_COLOR_CHOCOLATE
#define SA_CORAL                    SA_COLOR_CORAL
#define SA_CORNSILK                 SA_COLOR_CORNSILK
#define SA_CRIMSON                  SA_COLOR_CRIMSON
#define SA_CYAN                     SA_COLOR_CYAN
#define SA_DARKBLUE                 SA_COLOR_DARKBLUE
#define SA_DARKCYAN                 SA_COLOR_DARKCYAN
#define SA_DARKGOLDENROD            SA_COLOR_DARKGOLDENROD
#define SA_TEAL                     SA_COLOR_TEAL
#define SA_VIOLET                   SA_COLOR_VIOLET
#define SA_WHITESMOKE               SA_COLOR_WHITESMOKE
#define SA_YELLOW                   SA_COLOR_YELLOW
#define SA_TAN                      SA_COLOR_TAN
#define SA_SNOW                     SA_COLOR_SNOW
#define SA_DEEPSKYBLUE              SA_COLOR_DEEPSKYBLUE
#define SA_SILVER                   SA_COLOR_SILVER
#define SA_ROYALBLUE                SA_COLOR_ROYALBLUE
#define SA_INDIGO                   SA_COLOR_INDIGO
#define SA_MAROON                   SA_COLOR_MAROON
#define SA_NAVY                     SA_COLOR_NAVY


