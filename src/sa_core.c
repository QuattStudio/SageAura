/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#include "sa_core.h"
#include "glh.h"



#include <stdlib.h>






#ifdef _WIN32
    #include <windows.h>
#elif defined(__unix__) || defined(__APPLE__) || defined(_POSIX_C_SOURCE)
    #include <time.h>      // for nanosleep (best precision)
    #include <unistd.h>    // fallback usleep
#endif

void SA_Delay(int ms)
{
    if (ms <= 0) return;   // ignore negative or zero

#ifdef _WIN32
    Sleep((DWORD)ms);      // Windows: milliseconds
#else
    // POSIX (Linux, macOS, etc.)
    #if _POSIX_C_SOURCE >= 199309L
        struct timespec ts;
        ts.tv_sec  = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000L;
        nanosleep(&ts, NULL);
    #else
        usleep((useconds_t)ms * 1000);   // microseconds
    #endif
#endif
}




SA_Mesh* SA_CreateMesh_I(SA_Uint VAO, SA_Uint VBO, SA_Uint EBO)
{
    SA_Mesh* mesh = SA_MALLOC(SA_Mesh);
    if (!mesh) return NULL;

    mesh->VAO = VAO;
    mesh->VBO = VBO;
    mesh->EBO = EBO;
    mesh->VertexCount = 0;
    mesh->IndexCount = 0;

    return mesh;
}




void SA_MeshCounterReset_I(SA_Mesh* mesh)
{
    if (SA_NOT mesh) {
        SA_LOG_WARN("Nothing provided to reset in mesh counter reset function!");
        return;
    }

    mesh->VertexCount = 0;
    mesh->IndexCount = 0;
}





void SA_DestroyMesh_I(SA_Mesh* mesh)
{
    if (SA_NOT mesh) {
        SA_LOG_WARN("No mesh provided for destruction!");
        return;
    }


    GLH_DelVAO(&mesh->VAO, 1);
    GLH_DelBuffers(&mesh->VBO, 1);
    GLH_DelBuffers(&mesh->EBO, 1);

    SA_LOG_INFO("Mesh Destroyed succesfully!");

    free(mesh);

    mesh = NULL;
}



