/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once



#include "sa_common.h"
#include "sa_types.h"

#include "sa_platforms.h"




typedef struct SA_Mesh SA_Mesh;
typedef struct SA_Vertex SA_Vertex;

/////// /////////////// /////////////// ////////////////// ///////////////

SA_API void SA_Delay(int ms);
SA_Mesh* SA_CreateMesh_I(SA_Uint VAO, SA_Uint VBO, SA_Uint EBO);
void SA_DestroyMesh_I(SA_Mesh* mesh);









// typedefs struct

typedef struct SA_Mesh {
    SA_Uint VAO;
    SA_Uint VBO;
    SA_Uint EBO;

    int IndexCount;
    int VertexCount;
} SA_Mesh;




typedef struct SA_Vertex {
    float x, y;
    float r, g, b, a;
    float u, v;
} SA_Vertex;




// exceptions types

#define SA_RET_TYPE_NONE_I


#define SA_CHECK_WINDOW_I(window, msg, retType)\
    if (!window) {\
        SA_LOG_ERROR(msg);\
        return retType;\
    }



// exceptions msg

#define SA_MSG_WINDOW_NOT_FOUND_I    "SageAura Window not found!"