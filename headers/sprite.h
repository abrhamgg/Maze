#ifndef SPRITE_H
#define SPRITE_H

#include "graphics.h"
#include "defs.h"
#include "player.h"
#include "textures.h"
#include "ray.h"

/**
 * struct sprite_n - sprite properties
 * @x: x-position
 * @y: y-position
 * @distance: distance
 * @angle: angle
 * @visible: can the player see the sprite.
 * @texture: texture
 *
 * Description: sprite definition
 *
 */
typedef struct sprite_n
{
	float x;
	float y;
	float distance;
	float angle;
	bool visible;
	int texture;
} sprite_t;

void render_sprite_projection(void);
void render_map_sprites(void);

#endif
