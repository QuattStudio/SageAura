#include "sa_text.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"   // put stb_truetype.h in src/ or external/include/


#include "sa_inc.h"
#include "sa_renderer.h"

#include "glh.h"
#include "sa_algo.h"

#include "sa_common.h"




// ────────────────────────────────────────────────
// Text / Font support (embedded in renderer)
// ────────────────────────────────────────────────

typedef struct SA_Font {
    stbtt_fontinfo     info;
    GLuint             texID;
    int                atlasW, atlasH;
    stbtt_packedchar   chardata[128];     // 32..126 + some margin
    float              size;
    float              ascent, descent, linegap;
} SA_Font;

























SA_Font* SA_CreateFont(const char* ttf_path, float pixel_size)
{
    SA_Font* f = calloc(1, sizeof(SA_Font));
    
    if (SA_NOT f) {
        SA_LOG_WARN("allocation failed while creating a font!");
        return NULL;
    }


    FILE* fp = fopen(ttf_path, "rb");
    if (SA_NOT fp) {
        SA_LOG_WARN("Failed to access ttf file of path [%s]", ttf_path); 
        free(f); 
        return NULL; 
    }


    fseek(fp, 0, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);


    unsigned char* buf = malloc(sz);
    fread(buf, 1, sz, fp);
    fclose(fp);

    if (SA_NOT stbtt_InitFont(&f->info, buf, 0)) {
        SA_LOG_WARN("Font Init Failed! Font path: %s", ttf_path);
        free(buf); 
        free(f); 
        return NULL;
    }

    f->size = pixel_size;

    int ascent, descent, linegap;
    stbtt_GetFontVMetrics(&f->info, &ascent, &descent, &linegap);

    float scale = stbtt_ScaleForPixelHeight(&f->info, pixel_size);
    f->ascent   = ascent   * scale;
    f->descent  = descent  * scale;
    f->linegap  = linegap  * scale;

    // Atlas
    f->atlasW = 512;
    f->atlasH = 512;
    SA_Uint8* alpha_map = calloc(f->atlasW * f->atlasH, 1);

    stbtt_pack_context pc;
    stbtt_PackBegin(&pc, alpha_map, f->atlasW, f->atlasH, 0, 1, NULL);
    stbtt_PackSetOversampling(&pc, 2, 2);
    stbtt_PackFontRange(&pc, buf, 0, pixel_size, 32, 95, f->chardata + 32);
    stbtt_PackEnd(&pc);

    // Make RGBA white + alpha (so original shader tex * vertexColor works perfectly)
    SA_Uint8* rgba = malloc(f->atlasW * f->atlasH * 4);
    for (int i = 0; i < f->atlasW * f->atlasH; i++) {
        rgba[i*4 + 0] = 255;
        rgba[i*4 + 1] = 255;
        rgba[i*4 + 2] = 255;
        rgba[i*4 + 3] = alpha_map[i];
    }

    GLH_SetupTex2D(&f->texID, 1);
    glTexImage2D(GLH_TEX2D, 0, GL_RGBA, f->atlasW, f->atlasH, 0, GL_RGBA, GLH_UBYTE, rgba);

    GLH_SetTex2Dparami(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLH_SetTex2Dparami(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLH_BindTex2D(CurrentBoundTexture);

    free(buf);
    free(alpha_map);
    free(rgba);

    SA_LOG_INFO("Font loaded → texID = %u, size=%.1f", f->texID, pixel_size);
    SA_LOG_INFO("Atlas uploaded, bound tex now %u", CurrentBoundTexture);

    return f;
}


















void SA_DrawText(SA_Font* font, const char* str, float x, float y, SA_Colori color)
{
    if (!font || !str || !*str) return;

    if (CurrentBoundTexture != font->texID) {
        SA_FlushBatch();
        GlobalMesh->VertexCount = 0;
        GlobalMesh->IndexCount  = 0;
        CurrentBoundTexture = font->texID;
    }



    float cx = x;
    float cy = y + font->ascent;

    SA_Color fc = SA_NormalizeColorEx(color);

    while (*str) {
        int ch = (unsigned char)*str++;
        if (ch < 32 || ch > 126) {
            if (ch == ' ') cx += font->size * 0.45f;
            continue;
        }

        stbtt_aligned_quad q;
        stbtt_GetPackedQuad(font->chardata, font->atlasW, font->atlasH,
                            ch, &cx, &cy, &q, 1);   // 1 = use align (baseline)

        // Push quad (using your existing helpers)
        size_t base = GlobalMesh->VertexCount;

        SA_PushVertexUV(q.x0, q.y0, fc, q.s0, q.t0);
        SA_PushVertexUV(q.x1, q.y0, fc, q.s1, q.t0);
        SA_PushVertexUV(q.x0, q.y1, fc, q.s0, q.t1);
        SA_PushVertexUV(q.x1, q.y1, fc, q.s1, q.t1);

        SA_PushIndex(base+0); SA_PushIndex(base+1); SA_PushIndex(base+2);
        SA_PushIndex(base+1); SA_PushIndex(base+3); SA_PushIndex(base+2);

        if (GlobalMesh->VertexCount >= SA_MAX_VERTICES - 4) {
            SA_FlushBatch();
            GlobalMesh->VertexCount = 0;
            GlobalMesh->IndexCount  = 0;
        }
    }

    SA_FlushBatch();  // force draw text this frame
}








void SA_UnLoadFont(SA_Font* font)
{
    if (SA_NOT font) {
        SA_LOG_INFO("No font provide to UnLoad!");
        return;
    }


    glDeleteTextures(1, &font->texID);
    free(font);
    font = NULL;

    SA_LOG_INFO("Font UnLoaded Successfully!");
}