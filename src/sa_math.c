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








#define SA_ToRadians(deg) ((deg) * (3.14159265f / 180.0f))
#define SA_ToDegrees(rad) ((rad) * (180.0f / 3.14159265f))


