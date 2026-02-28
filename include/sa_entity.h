#pragma once


#include "core/sa_types.h"
#include "sa_platforms.h"
#include "sa_image.h"



typedef SA_Uint32 SA_Entity;




SA_API SA_Entity SA_SpawnEntity();


SA_API SA_Position* SA_EntityGetPosition(SA_Entity entity);
SA_API void SA_EntitySetPosition(SA_Entity entity, float x, float y);





SA_API SA_Velocity* SA_EntityGetVelocity(SA_Entity entity);
SA_API void SA_EntitySetVelocity(SA_Entity entity, float x, float y);


SA_API void SA_EntitiesUpdate(float DeltaTime);




SA_API void SA_EntityGiveSprite(SA_Entity entity, SA_Texture* texture, SA_Rect rect);
SA_API SA_Sprite* SA_EntityGetSprite(SA_Entity entity);


SA_API
SA_Sprite* SA_EntityGetSprite(SA_Entity entity);



SA_API
// void SA_EntitiesUpdateSprite();
void SA_DrawAllSprites(void);