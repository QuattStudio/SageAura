/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once



#include "core/sa_core.h"
#include "core/sa_types.h"

#include "sa_platforms.h"







#define SA_MAX_TRIANGLES    0x1388  // 5k
#define SA_MAX_INDICES      0x7530  // 30k  
#define SA_MAX_VERTICES     (SA_MAX_TRIANGLES * 3)



extern SA_Vertex sa_vertex_I[SA_MAX_VERTICES];
extern SA_Uint   sa_index_I[SA_MAX_INDICES];

extern SA_Mesh* GlobalMesh;
extern SA_Uint CurrentBoundTexture;






typedef struct SA_Texture {
    SA_Uint id;
    int width, height;
} SA_Texture;



extern SA_Texture* SA_WhiteTexture;   // global white texture for colored draws
extern int uModelLoc;



// SA_API
int SA_InitRenderer_I(void);


SA_API
void SA_PushIndex(SA_Uint idx);


// Simple vertex push (you can use this directly)
SA_API
void SA_PushVertex(float x, float y, SA_Color color);


SA_API
void SA_PushVertexUV(float x, float y, SA_Color color, float u, float v);



SA_API
void SA_DrawTriangle(
    int x1, int y1, SA_Colori color1,
    int x2, int y2, SA_Colori color2,
    int x3, int y3, SA_Colori color3);




SA_API
void SA_DrawRect(int x, int y, int w, int h, SA_Colori color);




SA_API
void SA_SetProjectionOrtho(float left, float right, float bottom, float top);




SA_API
void SA_FlushBatch(void);






SA_API
void SA_DrawPoint(int x, int y, SA_Colori color);



SA_API
void SA_DrawLine(int x0, int y0, int x1, int y1, SA_Colori color);