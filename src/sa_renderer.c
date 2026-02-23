/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

/* includes */

// internals
#include "sa_.h"

// others

#include "sa_renderer.h"

#include "sa_window.h"

#include "sa_inc.h"
#include "sa_algo.h"

#include "sa_common.h"
#include "sa_shaders.h"

#include "glh.h"


// Include End //





/* globals & statics */

SA_Vertex sa_vertex_I[SA_MAX_VERTICES];
SA_Uint sa_index_I[SA_MAX_INDICES];

static SA_Uint ShaderProgram;
SA_Mesh* GlobalMesh = NULL;


// add near existing globals
SA_Texture* SA_WhiteTexture = NULL; // white 1x1 texture
SA_Uint CurrentBoundTexture = 0; // 0 means white








static void SA_CreateWhiteTexture_I(void)
{
    unsigned char white[4] = { 255, 255, 255, 255 };
    SA_WhiteTexture = SA_MALLOC(SA_Texture);
    glGenTextures(1, &SA_WhiteTexture->id);
    glBindTexture(GL_TEXTURE_2D, SA_WhiteTexture->id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
    GLH_GenMipmap(GLH_TEX2D);

    GLH_SetTexparami(GL_TEXTURE_WRAP_S, GL_REPEAT);
    GLH_SetTexparami(GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLH_SetTexparami(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    GLH_SetTexparami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SA_WhiteTexture->width = 1;
    SA_WhiteTexture->height = 1;
}






int SA_InitRenderer_I(void)
{
    SA_LOG_INFO("[Side: Renderer] > Setting up Renderer...");


    


        /* Load GLAD */
    if (SA_NOT GLH_GL_Load()) {
        SA_LOG_ERROR("GLAD Loading failed!");
        SA_CheckIsControlFlagEnabled_I(SA_FALSE);
    }

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    SA_Uint VAO, VBO, EBO;


    GLH_SetupVAO(&VAO, 1);

    SA_LOGV_INFO("VAO Setup Completed!");

    GLH_SetBufferDataFast(GLH_VBO, &VBO, NULL, sizeof(SA_Vertex) * SA_MAX_VERTICES, 1);
    GLH_SetBufferDataFast(GLH_EBO, &EBO, NULL, sizeof(SA_Uint) * SA_MAX_INDICES, 1);
    

    SA_LOGV_INFO("VBO allocated for max %d vertices (%zu MB)", 
             SA_MAX_VERTICES, 
             (sizeof(SA_Vertex) * SA_MAX_VERTICES) / (1024*1024));

    SA_LOGV_INFO("VBO & EBO Setup Completed!");



    // stride is sizeof(SA_Vertex)
    GLsizei stride = (GLsizei)sizeof(SA_Vertex);

    // position: location 0, vec2
    GLH_SetVertexAttrib(0, 2, GL_FLOAT, GL_FALSE, stride, SA_OFFSET(0));

    // color: location 1, vec4; offset = 2 * sizeof(float)
    GLH_SetVertexAttrib(1, 4, GL_FLOAT, GL_FALSE, stride, SA_OFFSET(2 * sizeof(float)));

    // texcoord: location 2, vec2; offset = 6 * sizeof(float)
    GLH_SetVertexAttrib(2, 2, GL_FLOAT, GL_FALSE, stride, SA_OFFSET(6 * sizeof(float)));


    SA_LOGV_INFO("Vertex Atrribute setted!");


    SA_Uint VertexShader = GLH_CompileShader(&SA_VertexShaderSrc_I, 1, GL_VERTEX_SHADER);
    SA_LOGV_INFO("Vertex Shader compiled successfully!");
    
    SA_Uint FragmentShader = GLH_CompileShader(&SA_FragmentShaderSrc_I, 1, GL_FRAGMENT_SHADER);
    SA_LOGV_INFO("Fragment Shader compiled successfully!");


    ShaderProgram = GLH_CreateProgram(VertexShader, FragmentShader); // compile & link
    SA_LOGV_INFO("Renderer program created successfully!");

    glUseProgram(ShaderProgram);
    GLint loc = glGetUniformLocation(ShaderProgram, "uTexture");
    if (loc >= 0) {
        glUniform1i(loc, 0); // texture unit 0
    }


    GlobalMesh = SA_CreateMesh_I(VAO, VBO, EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GLH_EBO, EBO);
    glBindVertexArray(0);


    SA_CreateWhiteTexture_I();
    CurrentBoundTexture = SA_WhiteTexture ? SA_WhiteTexture->id : 0;

    SA_LOG_INFO("[Side: Renderer] > Renderer Init completed!");
}













void SA_PushIndex(SA_Uint idx)
{
    if (GlobalMesh->IndexCount >= SA_MAX_INDICES) {
        SA_FlushBatch();
        SA_MeshCounterReset_I(GlobalMesh);
    }
    sa_index_I[GlobalMesh->IndexCount++] = idx;
}






void SA_PushVertex(float x, float y, SA_Color color)
{
    if (GlobalMesh->VertexCount >= SA_MAX_VERTICES || 
        GlobalMesh->IndexCount >= SA_MAX_INDICES - 6) {   // safety margin
        SA_FlushBatch();
        SA_MeshCounterReset_I(GlobalMesh);
    }

    SA_Vertex* vertex = &sa_vertex_I[GlobalMesh->VertexCount++];
    vertex->x = x; 
    vertex->y = y;

    vertex->r = color.r; 
    vertex->g = color.g; 
    vertex->b = color.b; 
    vertex->a = color.a;

    // default
    vertex->u = 0.0f; 
    vertex->v = 0.0f; 
}





void SA_PushVertexUV(float x, float y, SA_Color color, float u, float v)
{
    if (GlobalMesh->VertexCount >= SA_MAX_VERTICES ||
        GlobalMesh->IndexCount >= SA_MAX_INDICES - 6) {
        SA_FlushBatch();
        SA_MeshCounterReset_I(GlobalMesh);
    }

    SA_Vertex* vertex = &sa_vertex_I[GlobalMesh->VertexCount++];
    vertex->x = x; 
    vertex->y = y;

    vertex->r = color.r; 
    vertex->g = color.g; 
    vertex->b = color.b; 
    vertex->a = color.a;

    vertex->u = u; 
    vertex->v = v;
}




void SA_DrawTriangle(
    int x1, int y1, SA_Colori color1,
    int x2, int y2, SA_Colori color2,
    int x3, int y3, SA_Colori color3)
{
    SA_Uint whiteId = SA_WhiteTexture ? SA_WhiteTexture->id : 0;
    if (CurrentBoundTexture != whiteId) {
        SA_FlushBatch();
        SA_MeshCounterReset_I(GlobalMesh);
        CurrentBoundTexture = whiteId;
    }

    size_t base = GlobalMesh->VertexCount;

    
    SA_Color fcolor1;
    SA_Color fcolor2;
    SA_Color fcolor3;
    fcolor1 = SA_NormalizeColorEx(color1);
    fcolor2 = SA_NormalizeColorEx(color2);
    fcolor3 = SA_NormalizeColorEx(color3);


    SA_PushVertex((float)x1, (float)y1, fcolor1);
    SA_PushVertex((float)x2, (float)y2, fcolor2);
    SA_PushVertex((float)x3, (float)y3, fcolor3);

    SA_PushIndex(base + 0);
    SA_PushIndex(base + 1);
    SA_PushIndex(base + 2);
}




void SA_DrawRect(int x, int y, int w, int h, SA_Colori color)
{
    SA_Uint whiteId = SA_WhiteTexture ? SA_WhiteTexture->id : 0;
    if (CurrentBoundTexture != whiteId) {
        SA_FlushBatch();
        SA_MeshCounterReset_I(GlobalMesh);
        CurrentBoundTexture = whiteId;
    }

    size_t base = GlobalMesh->VertexCount;   // starting index for this rect

    SA_Color fcolor;
    fcolor = SA_NormalizeColorEx(color);

    // Push 4 vertices (counter-clockwise order)
    SA_PushVertex((float)x,     (float)y,     fcolor);   // 0 top-left
    SA_PushVertex((float)x + w, (float)y,     fcolor);   // 1 top-right
    SA_PushVertex((float)x,     (float)y + h, fcolor);   // 2 bottom-left
    SA_PushVertex((float)x + w, (float)y + h, fcolor);   // 3 bottom-right

    // Push 6 indices (two triangles)
    SA_PushIndex(base + 0);
    SA_PushIndex(base + 1);
    SA_PushIndex(base + 2);

    SA_PushIndex(base + 1);
    SA_PushIndex(base + 3);
    SA_PushIndex(base + 2);
}




void SA_SetProjectionOrtho(float left, float right, float bottom, float top)
{
    float ortho[16] = {
        2.0f/(right-left),  0,                  0, 0,
        0,                  2.0f/(top-bottom),  0, 0,
        0,                  0,                 -1, 0,
        -(right+left)/(right-left), -(top+bottom)/(top-bottom), 0, 1
    };

    GLint loc = glGetUniformLocation(ShaderProgram, "uProjection");
    glUseProgram(ShaderProgram);
    glUniformMatrix4fv(loc, 1, GL_FALSE, ortho);
}











void SA_FlushBatch(void)
{
    if (GlobalMesh->IndexCount == 0) return;

    
    // Upload VBO data
    glBindBuffer(GLH_VBO, GlobalMesh->VBO);
    glBufferSubData(GLH_VBO, 0,
                    GlobalMesh->VertexCount * sizeof(SA_Vertex),
                    sa_vertex_I);

    
    // Upload EBO data
    glBindBuffer(GLH_EBO, GlobalMesh->EBO);
    glBufferSubData(GLH_EBO, 0,
                    GlobalMesh->IndexCount * sizeof(SA_Uint),
                    sa_index_I);

                    
    glUseProgram(ShaderProgram);
    GLH_BindVAO(GlobalMesh->VAO);

    // bind texture to unit 0 (use white texture if none set)
    SA_Uint texToBind = CurrentBoundTexture;
    if (texToBind == 0 && SA_WhiteTexture) texToBind = SA_WhiteTexture->id;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GLH_TEX2D, texToBind);

    // draw
    GLH_DrawTriElms((GLsizei)GlobalMesh->IndexCount, GLH_UINT, 0);

    // unbind
    glBindVertexArray(0);

}
























