#include "sa_math.h"

#include <math.h>










SA_Vec2 SA_Vec2_Create(float x, float y)
{
    return (SA_Vec2){x, y};
}





SA_Vec2i SA_Vec2i_Create(int x, int y)
{
    return (SA_Vec2i){x, y};
}








SA_Vec2 SA_Vec2_Add(SA_Vec2 vector1, SA_Vec2 vector2)
{
    return (SA_Vec2){vector1.x + vector2.x, vector1.y + vector2.y};
}



SA_Vec2i SA_Vec2i_Add(SA_Vec2i vector1, SA_Vec2i vector2)
{
    return (SA_Vec2i){vector1.x + vector2.x, vector1.y + vector2.y};
}






SA_Vec2 SA_Vec2_Sub(SA_Vec2 vector1, SA_Vec2 vector2)
{
    return (SA_Vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}



SA_Vec2i SA_Vec2i_Sub(SA_Vec2i vector1, SA_Vec2i vector2)
{
    return (SA_Vec2i){vector1.x - vector2.x, vector1.y - vector2.y};
}







SA_Vec2 SA_Vec2_Scale(SA_Vec2 vector, float scale)
{
    return (SA_Vec2){vector.x * scale, vector.y * scale};
}


SA_Vec2i SA_Vec2i_Scale(SA_Vec2i vector, int scale)
{
    return (SA_Vec2i){vector.x * scale, vector.y * scale};
}





float SA_Vec2_Length(SA_Vec2 vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y);
}



float SA_Vec2i_Length(SA_Vec2i vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}




SA_Vec2 SA_Vec2_Normalize(SA_Vec2 vector)
{
    float len = SA_Vec2_Length(vector);

    if (len == 0.0f) 
        return (SA_Vec2){0, 0};

    return (SA_Vec2){vector.x / len, vector.y / len};
}



SA_Vec2 SA_Vec2i_Normalize(SA_Vec2i vector) {
    float len = SA_Vec2i_Length(vector);
    if (len == 0.0f) return (SA_Vec2){0, 0};
    return (SA_Vec2){vector.x / len, vector.y / len};
}






float SA_Vec2_Distance(SA_Vec2 vector1, SA_Vec2 vector2)
{
    return SA_Vec2_Length(SA_Vec2_Sub(vector1, vector2));
}




float SA_Vec2i_Distance(SA_Vec2i vector1, SA_Vec2i vector2)
{
    return SA_Vec2i_Length(SA_Vec2i_Sub(vector1, vector2));
}




SA_Vec2 SA_Vec2_Lerp(SA_Vec2 vector1, SA_Vec2 vector2, float t)
{
    return (SA_Vec2){vector1.x + (vector2.x - vector1.x) * t, vector1.y + (vector2.y - vector1.y) * t};
}



SA_Vec2i SA_Vec2i_Lerp(SA_Vec2i vector1, SA_Vec2i vector2, float t )
{
    return (SA_Vec2i){vector1.x + (vector2.x - vector1.x) * t, vector1.y + (vector2.y - vector1.y) * t};
}


/////* matrix */////





void SA_Mat4Identity(float* m)
{
    for(int i=0;i<16;i++) m[i] = 0.0f;

    m[0] = 1.0f;
    m[5] = 1.0f;
    m[10] = 1.0f;
    m[15] = 1.0f;
}




void SA_Mat4Multiply(float* result, const float* a, const float* b)
{
    float r[16];

    for(int row=0; row<4; row++)
    for(int col=0; col<4; col++)
    {
        r[row*4+col] =
            a[row*4+0]*b[0*4+col] +
            a[row*4+1]*b[1*4+col] +
            a[row*4+2]*b[2*4+col] +
            a[row*4+3]*b[3*4+col];
    }

    for(int i=0;i<16;i++)
        result[i] = r[i];
}



void SA_Mat4Translate(float* m, float x, float y)
{
    float t[16];
    SA_Mat4Identity(t);

    t[12] = x;
    t[13] = y;

    SA_Mat4Multiply(m, m, t);
}




void SA_Mat4Scale(float* m, float sx, float sy)
{
    float s[16];
    SA_Mat4Identity(s);

    s[0] = sx;
    s[5] = sy;

    SA_Mat4Multiply(m, m, s);
}





#include <math.h>

void SA_Mat4RotateZ(float* m, float degrees)
{
    float r[16];
    SA_Mat4Identity(r);

    float rad = degrees * 0.01745329251f; // deg → rad
    float c = cosf(rad);
    float s = sinf(rad);

    r[0] =  c;
    r[1] =  s;
    r[4] = -s;
    r[5] =  c;

    SA_Mat4Multiply(m, m, r);
}




// void SA_BuildModelMatrix(float* m,
//                          float x, float y,
//                          float rotationDeg,
//                          float sx, float sy)
// {
//     float r = rotationDeg * 0.01745329251f; // radians
//     float c = cosf(r);
//     float s = sinf(r);

//     // column-major order (OpenGL)
//     m[0] =  c * sx;
//     m[1] =  s * sx;
//     m[2] =  0;
//     m[3] =  0;

//     m[4] = -s * sy;
//     m[5] =  c * sy;
//     m[6] =  0;
//     m[7] =  0;

//     m[8]  = 0;
//     m[9]  = 0;
//     m[10] = 1;
//     m[11] = 0;

//     m[12] = x;
//     m[13] = y;
//     m[14] = 0;
//     m[15] = 1;
// }




void SA_BuildModelMatrix(float* m,
                         float x, float y,
                         float rotation,
                         float scaleX, float scaleY,
                         float w, float h)
{
    float cx = w * 0.5f;
    float cy = h * 0.5f;

    SA_Mat4Identity(m);

    // move to position
    SA_Mat4Translate(m, x + cx, y + cy);

    // rotate
    SA_Mat4RotateZ(m, rotation);

    // scale
    SA_Mat4Scale(m, scaleX, scaleY);

    // move pivot back
    SA_Mat4Translate(m, -cx, -cy);
}


#define SA_ToRadians(deg) ((deg) * (3.14159265f / 180.0f))
#define SA_ToDegrees(rad) ((rad) * (180.0f / 3.14159265f))


