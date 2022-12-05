#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "defs.h"
#include "map.h"
#include "graphics.h"
#include "ray.h"

/**
 * struct player_n - player definitoin
 * @x: xposition
 * @y: y-position
 * @width: widthof player
 * @height: height of player
 * @turn_direction: turn direction
 * @walk_direction: walk_direction
 * @roatation_angle: rotation angle
 * @walk_speed: walk speed
 * @turn_speed: turn speed
 *
 * Description: player properties definition
 */
typedef struct player_n
{
	float x;
	float y;
	float width;
	float height;
	int turn_direction;
	int walk_direction;
	float roatation_angle;
	float walk_speed;
	float turn_speed;
} player_t;

extern player_t player;
void move_player(float delta_time);
void render_map_player(void);

#endif
