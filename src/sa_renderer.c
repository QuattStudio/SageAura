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


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



// Include End //





/* globals & statics */

SA_Vertex sa_vertex_I[SA_MAX_VERTICES];
SA_Uint sa_index_I[SA_MAX_INDICES];

static SA_Uint ShaderProgram;
SA_Mesh* GlobalMesh = NULL;


// add near existing globals
SA_Texture* SA_WhiteTexture = NULL; // white 1x1 texture
static SA_Uint CurrentBoundTexture = 0; // 0 means white



// globals & statics End //



static void SA_CreateWhiteTexture_I(void)
{
    unsigned char white[4] = { 255, 255, 255, 255 };
    SA_WhiteTexture = SA_MALLOC(SA_Texture);
    glGenTextures(1, &SA_WhiteTexture->id);
    glBindTexture(GL_TEXTURE_2D, SA_WhiteTexture->id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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


    // GLH_SetVertexAttrib(0, 2, GL_FLOAT, GL_FALSE, sizeof(SA_Vertex), NULL);
    // GLH_SetVertexAttrib(1, 4, GL_FLOAT, GL_FALSE, sizeof(SA_Vertex), (void*)(2*sizeof(float)) );

    // assuming VAO,VBO,EBO created earlier...
    // stride is sizeof(SA_Vertex)
    GLsizei stride = (GLsizei)sizeof(SA_Vertex);

    // position: location 0, vec2
    GLH_SetVertexAttrib(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)(0));

    // color: location 1, vec4; offset = 2 * sizeof(float)
    GLH_SetVertexAttrib(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));

    // texcoord: location 2, vec2; offset = 6 * sizeof(float)
    GLH_SetVertexAttrib(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));


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
        GlobalMesh->VertexCount = 0;
        GlobalMesh->IndexCount  = 0;
    }
    sa_index_I[GlobalMesh->IndexCount++] = idx;
}






void SA_PushVertex(float x, float y, float r, float g, float b, float a)
{
    if (GlobalMesh->VertexCount >= SA_MAX_VERTICES || 
        GlobalMesh->IndexCount >= SA_MAX_INDICES - 6) {   // safety margin
        SA_FlushBatch();
        GlobalMesh->VertexCount = 0;
        GlobalMesh->IndexCount  = 0;
    }

    SA_Vertex* v = &sa_vertex_I[GlobalMesh->VertexCount++];
    v->x = x; v->y = y;
    v->r = r; v->g = g; v->b = b; v->a = a;
    v->u = 0.0f; v->v = 0.0f; // default
}





void SA_PushVertexUV(float x, float y, float r, float g, float b, float a, float u, float v)
{
    if (GlobalMesh->VertexCount >= SA_MAX_VERTICES ||
        GlobalMesh->IndexCount >= SA_MAX_INDICES - 6) {
        SA_FlushBatch();
        GlobalMesh->VertexCount = 0;
        GlobalMesh->IndexCount = 0;
    }

    SA_Vertex* vtx = &sa_vertex_I[GlobalMesh->VertexCount++];
    vtx->x = x; vtx->y = y;
    vtx->r = r; vtx->g = g; vtx->b = b; vtx->a = a;
    vtx->u = u; vtx->v = v;
}





SA_Texture* SA_LoadTexture(const char* filepath)
{
    int w, h, channels;
    // stbi_set_flip_vertically_on_load(SA_TRUE);   // OpenGL needs this

    unsigned char* data = stbi_load(filepath, &w, &h, &channels, 4); // force RGBA
    if (!data) {
        SA_LOG_ERROR("Failed to load image: %s", filepath);
        return NULL;
    }

    SA_Texture* tex = SA_MALLOC(SA_Texture);
    // GLH_SetupTex2D(&tex, 1);
    glGenTextures(1, &tex->id);
    glBindTexture(GL_TEXTURE_2D, tex->id);


    glTexImage2D(GLH_TEX2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GLH_UBYTE, data);
    GLH_GenMipmap(GLH_TEX2D);


    GLH_SetTex2Dparami(GL_TEXTURE_WRAP_S, GL_REPEAT);
    GLH_SetTex2Dparami(GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLH_SetTex2Dparami(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    GLH_SetTex2Dparami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    stbi_image_free(data);

    tex->width = w;
    tex->height = h;
    return tex;
}





// u0,v0 = top-left texcoord, u1,v1 = bottom-right texcoord
void SA_DrawTexture(SA_Texture* tex, int x, int y, int w, int h)
{
    // if texture changed -> flush batch
    SA_Uint texId = tex ? tex->id : (SA_WhiteTexture ? SA_WhiteTexture->id : 0);
    if (texId != CurrentBoundTexture) {
        SA_FlushBatch();
        GlobalMesh->VertexCount = 0;
        GlobalMesh->IndexCount = 0;
        CurrentBoundTexture = texId;
    }

    size_t base = GlobalMesh->VertexCount;

    float u0, v0, u1, v1;
    u0 = 0.0f;
    v0 = 0.0f;
    u1 = 1.0f;
    v1 = 1.0f;

    /*
        we normallizing because ...
        I don't Known

        may be because previously SA_DrawImage function explicity takes tint of an image so
        we normalize it but now just for laziness of few lines we write directly also
        writing 1.0f is weird at least for me.

    */

    SA_ColorF fcolor;
    fcolor = SA_NormalizeColorEx(255, 255, 255, 255); // white color

    // Note: choose vertex ordering consistent with your coordinate system
    SA_PushVertexUV((float)x,     (float)y,      fcolor.r, fcolor.g, fcolor.b, fcolor.a, u0, v0); // top-left
    SA_PushVertexUV((float)x + w, (float)y,      fcolor.r, fcolor.g, fcolor.b, fcolor.a, u1, v0); // top-right
    SA_PushVertexUV((float)x,     (float)y + h,  fcolor.r, fcolor.g, fcolor.b, fcolor.a, u0, v1); // bottom-left
    SA_PushVertexUV((float)x + w, (float)y + h,  fcolor.r, fcolor.g, fcolor.b, fcolor.a, u1, v1); // bottom-right

    SA_PushIndex((SA_Uint)(base + 0));
    SA_PushIndex((SA_Uint)(base + 1));
    SA_PushIndex((SA_Uint)(base + 2));

    SA_PushIndex((SA_Uint)(base + 1));
    SA_PushIndex((SA_Uint)(base + 3));
    SA_PushIndex((SA_Uint)(base + 2));
}



void SA_UnLoadTexture(SA_Texture* texture)
{
    if (SA_NOT texture) return;
    free(texture);
}





void SA_DrawTriangle(
    int x1, int y1, SA_Color color1,
    int x2, int y2, SA_Color color2,
    int x3, int y3, SA_Color color3)
{
    SA_Uint whiteId = SA_WhiteTexture ? SA_WhiteTexture->id : 0;
    if (CurrentBoundTexture != whiteId) {
        SA_FlushBatch();
        GlobalMesh->VertexCount = 0;
        GlobalMesh->IndexCount = 0;
        CurrentBoundTexture = whiteId;
    }

    size_t base = GlobalMesh->VertexCount;

    
    SA_ColorF fcolor1;
    SA_ColorF fcolor2;
    SA_ColorF fcolor3;
    fcolor1 = SA_NormalizeColorEx(color1.r, color1.g, color1.b, color1.a);
    fcolor2 = SA_NormalizeColorEx(color2.r, color2.g, color2.b, color2.a);
    fcolor3 = SA_NormalizeColorEx(color3.r, color3.g, color3.b, color3.a);


    SA_PushVertex((float)x1, (float)y1, fcolor1.r, fcolor1.g, fcolor1.b, fcolor1.a);
    SA_PushVertex((float)x2, (float)y2, fcolor2.r, fcolor2.g, fcolor2.b, fcolor2.a);
    SA_PushVertex((float)x3, (float)y3, fcolor3.r, fcolor3.g, fcolor3.b, fcolor3.a);

    SA_PushIndex(base + 0);
    SA_PushIndex(base + 1);
    SA_PushIndex(base + 2);
}




void SA_DrawRect(int x, int y, int w, int h, SA_Color color)
{
    SA_Uint whiteId = SA_WhiteTexture ? SA_WhiteTexture->id : 0;
    if (CurrentBoundTexture != whiteId) {
        SA_FlushBatch();
        GlobalMesh->VertexCount = 0;
        GlobalMesh->IndexCount = 0;
        CurrentBoundTexture = whiteId;
    }

    size_t base = GlobalMesh->VertexCount;   // starting index for this rect

    SA_ColorF fcolor;
    fcolor = SA_NormalizeColorEx(color.r, color.g, color.b, color.a);

    // Push 4 vertices (counter-clockwise order)
    SA_PushVertex((float)x,     (float)y,     fcolor.r, fcolor.g, fcolor.b, fcolor.a);   // 0 top-left
    SA_PushVertex((float)x + w, (float)y,     fcolor.r, fcolor.g, fcolor.b, fcolor.a);   // 1 top-right
    SA_PushVertex((float)x,     (float)y + h, fcolor.r, fcolor.g, fcolor.b, fcolor.a);   // 2 bottom-left
    SA_PushVertex((float)x + w, (float)y + h, fcolor.r, fcolor.g, fcolor.b, fcolor.a);   // 3 bottom-right

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
    glBindBuffer(GL_ARRAY_BUFFER, GlobalMesh->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    GlobalMesh->VertexCount * sizeof(SA_Vertex),
                    sa_vertex_I);

    // Upload EBO data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GlobalMesh->EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
                    GlobalMesh->IndexCount * sizeof(SA_Uint),
                    sa_index_I);

    glUseProgram(ShaderProgram);
    GLH_BindVAO(GlobalMesh->VAO);

    // bind texture to unit 0 (use white texture if none set)
    SA_Uint texToBind = CurrentBoundTexture;
    if (texToBind == 0 && SA_WhiteTexture) texToBind = SA_WhiteTexture->id;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texToBind);

    // draw
    glDrawElements(GL_TRIANGLES,
                   (GLsizei)GlobalMesh->IndexCount,
                   GL_UNSIGNED_INT,
                   0);

    // Optional: unbind
    glBindVertexArray(0);

}