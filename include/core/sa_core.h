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

void SA_MeshCounterReset_I(SA_Mesh* mesh);




void SA_ApplyGLFWWindowHint_I(SA_Uint flags);



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





typedef struct SA_Timer {
    struct {
        SA_Uint32 start;
        SA_Uint32 last;
        SA_Uint32 current;
        float delta;
    } time;
} SA_Timer;



SA_API SA_Uint32 SA_GetTicks(void);

SA_API SA_Timer* SA_StartTimer(void);

SA_API void SA_StopTimer(SA_Timer* timer);
SA_API float SA_GetDeltaFromTimer(SA_Timer *timer);

SA_API float SA_GetElapsed(SA_Timer* timer);








typedef enum {
    SA_FLAG_NONE = 0,
    SA_FLAG_WINDOW_MAXIMIZED = (1 << 0),
    SA_FLAG_WINDOW_FULLSCREEN = (1 << 1),
    SA_FLAG_WINDOW_BORDERLESS = (1 << 2),
    SA_FLAG_WINDOW_RESIZABLE = (1 << 3),

    SA_FLAG_ENABLE_CONTROL = (1 << 4),
    // SA_FLAG_WINDOW_M = (0 << 1),
} SA_InitFlags_I;




#define SA_FLAG_MAXIMIZED   SA_FLAG_WINDOW_MAXIMIZED
#define SA_FLAG_BORDERLESS  SA_FLAG_WINDOW_BORDERLESS
#define SA_FLAG_RESIZABLE   SA_FLAG_WINDOW_RESIZABLE


#define SA_MAXIMIZED        SA_FLAG_MAXIMIZED
#define SA_BORDERLESS       SA_FLAG_BORDERLESS
#define SA_RESIZABLE        SA_FLAG_RESIZABLE


// exceptions types

#define SA_RET_TYPE_NONE_I


#define SA_CHECK_WINDOW_I(window, msg, retType)\
    if (!window) {\
        SA_LOG_ERROR(msg);\
        return retType;\
    }



// exceptions msg

#define SA_MSG_WINDOW_NOT_FOUND_I    "SageAura Window not found!"
#define SA_MSG_GLFW_WINDOW_NOT_FOUND_I    "GLFW Window not found!"