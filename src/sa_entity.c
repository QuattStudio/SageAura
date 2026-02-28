#include "sa_entity.h"
#include "sa_common.h"

#include "sa_colorl.h"

#include <stdlib.h>

#define SA_MAX_ENTITIES     0xffff
#define SA_INVALID_ENTITY   0








static SA_Uint32 SA_EntityFlags_I[SA_MAX_ENTITIES];
static SA_Position SA_EntityPos_I[SA_MAX_ENTITIES];
static SA_Velocity SA_EntityVel_I[SA_MAX_ENTITIES];
static SA_Sprite SA_EntitySprite_I[SA_MAX_ENTITIES];


typedef enum {
    SA_ENTITY_HAS_POSITION_I = (1 << 0),
    SA_ENTITY_HAS_VELOCITY_I = (1 << 1),
    SA_ENTITY_HAS_SPRITE = (1 << 2),
} SA_ComponentFlags_I;



#define SA_ENTITY_POS_AND_VEL_PRESENT_I       (SA_ENTITY_HAS_POSITION_I | SA_ENTITY_HAS_VELOCITY_I)



static SA_Uint32 SA_NextEntityId_I = 1;

SA_Entity SA_SpawnEntity() 
{
    if (SA_NextEntityId_I > SA_MAX_ENTITIES) return SA_INVALID_ENTITY;
    return SA_NextEntityId_I++;
}




static SA_Bool SA_EntityHasPosition(SA_Entity entity) {
    if (entity == SA_INVALID_ENTITY) return SA_FALSE;

    return (SA_EntityFlags_I[entity] & SA_ENTITY_HAS_POSITION_I) != 0;
}




SA_Position* SA_EntityGetPosition(SA_Entity entity) {
    if (entity == SA_INVALID_ENTITY) return NULL;

    return SA_EntityHasPosition(entity) SA_THEN &SA_EntityPos_I[entity] SA_ELSE NULL;
}



void SA_EntitySetPosition(SA_Entity entity, float x, float y) {
    if (entity == SA_INVALID_ENTITY) return;

    SA_EntityFlags_I[entity] |= SA_ENTITY_HAS_POSITION_I;
    SA_EntityPos_I[entity] = (SA_Position){x, y};
}











static SA_Bool SA_EntityHasVelocity(SA_Entity entity) {
    if (entity == SA_INVALID_ENTITY) return SA_FALSE;

    return (SA_EntityFlags_I[entity] & SA_ENTITY_HAS_VELOCITY_I) != 0;
}




SA_Velocity* SA_EntityGetVelocity(SA_Entity entity) {
    if (entity == SA_INVALID_ENTITY) return NULL;

    return SA_EntityHasVelocity(entity) SA_THEN &SA_EntityVel_I[entity] SA_ELSE NULL;
}



void SA_EntitySetVelocity(SA_Entity entity, float x, float y) {
    if (entity == SA_INVALID_ENTITY) return;

    SA_EntityFlags_I[entity] |= SA_ENTITY_HAS_VELOCITY_I;
    SA_EntityVel_I[entity] = (SA_Velocity){x, y};
}




void SA_EntitiesUpdate(float DeltaTime)
{
    for (int EntityCount = 1; EntityCount < SA_NextEntityId_I; EntityCount ++)
    {
        if ( ( SA_EntityFlags_I[EntityCount] & SA_ENTITY_POS_AND_VEL_PRESENT_I != 
                SA_ENTITY_POS_AND_VEL_PRESENT_I ) )
            continue;

        SA_EntityPos_I[EntityCount].x += SA_EntityVel_I[EntityCount].x * DeltaTime;
        SA_EntityPos_I[EntityCount].y += SA_EntityVel_I[EntityCount].y * DeltaTime;
     }
}










// Helper to check if entity has sprite (FIXED)
static SA_Bool SA_EntityHasSprite(SA_Entity entity) {
    if (entity == SA_INVALID_ENTITY) return SA_FALSE;
    return (SA_EntityFlags_I[entity] & SA_ENTITY_HAS_SPRITE) != 0;
}




// Get sprite pointer (FIXED - correct check + real ternary operator)
SA_Sprite* SA_EntityGetSprite(SA_Entity entity) {
    if (entity == SA_INVALID_ENTITY) return NULL;
    return SA_EntityHasSprite(entity) ? &SA_EntitySprite_I[entity] : NULL;
}




// Fixed sprite giving (looks mostly ok, but ensure rect is source rect)
void SA_EntityGiveSprite(SA_Entity entity, SA_Texture* texture, SA_Rect source_rect) {
    if (entity == SA_INVALID_ENTITY) return;
    SA_EntityFlags_I[entity] |= SA_ENTITY_HAS_SPRITE;
    SA_EntitySprite_I[entity] = (SA_Sprite){
        .texture = texture,
        .color   = SA_WHITE,
        .rect    = source_rect,   // this should be SOURCE rect (part of texture)
    };
}




void SA_DrawAllSprites(void)
{
    for (SA_Uint32 e = 1; e < SA_NextEntityId_I; e++)
    {
        if (!SA_EntityHasSprite(e)) continue;

        SA_Sprite*   sprite = SA_EntityGetSprite(e);
        SA_Position* pos    = SA_EntityGetPosition(e);

        // Skip if no position or no sprite data
        if (!pos || !sprite || !sprite->texture) continue;

        // Build the rect we pass to DrawTextureEx:
        //   - x,y     = current entity position
        //   - w,h     = size we want to draw (from sprite setup or texture size)
        SA_Rect draw_rect = {
            .x = pos->x,
            .y = pos->y,
            .width = sprite->rect.width,   // width you gave when calling SA_EntityGiveSprite
            .height = sprite->rect.height,
        };

        SA_DrawTextureEx(
            sprite->texture,
            &draw_rect,           // position + size
            sprite->color         // tint
        );
    }
}