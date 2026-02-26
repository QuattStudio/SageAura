#include "sa_image.h"



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#include "sa_algo.h"

#include "sa_renderer.h"
#include "glh.h"

#include "sa_common.h"
#include "sa_colorl.h"
#include "sa_math.h"


SA_Texture* SA_LoadTexture(const char* filepath)
{
    int w, h, channels;
    // stbi_set_flip_vertically_on_load(SA_TRUE);   // OpenGL needs this

    unsigned char* data = stbi_load(filepath, &w, &h, &channels, 4); // force RGBA
    if (!data) {
        SA_LOG_WARN("Failed to load image: %s", filepath);
        return NULL;
    }

    SA_Texture* tex = SA_MALLOC(SA_Texture);
    glGenTextures(1, &tex->id);
    glBindTexture(GLH_TEX2D, tex->id);


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

    SA_Color fcolor;
    fcolor = SA_NormalizeColorEx(SA_COLOR_WHITE);

    // Note: choose vertex ordering consistent with your coordinate system
    SA_PushVertexUV((float)x,     (float)y,      fcolor, u0, v0); // top-left
    SA_PushVertexUV((float)x + w, (float)y,      fcolor, u1, v0); // top-right
    SA_PushVertexUV((float)x,     (float)y + h,  fcolor, u0, v1); // bottom-left
    SA_PushVertexUV((float)x + w, (float)y + h,  fcolor, u1, v1); // bottom-right

    SA_PushIndex((SA_Uint)(base + 0));
    SA_PushIndex((SA_Uint)(base + 1));
    SA_PushIndex((SA_Uint)(base + 2));

    SA_PushIndex((SA_Uint)(base + 1));
    SA_PushIndex((SA_Uint)(base + 3));
    SA_PushIndex((SA_Uint)(base + 2));
}







void SA_UnloadTexture(SA_Texture* texture)
{
    if (SA_NOT texture) return;
    free(texture);
}

