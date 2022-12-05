#ifndef RAY_H
#define RAY_H

#include <stdbool.h>
#include "defs.h"
#include "player.h"
#include "limits.h"

/**
 * struct ray_n - ray properties
 * @ray_angle: ray_angle
 * @wall_hit_x: wall intersection x position
 * @wall_hit_y: wall intersection y position
 * @vertical_hit: vertical intersection
 * @distance: distance
 * @wall_hit_content: wall hit content.
 *
 * Description: ray properties
 *
 */
typedef struct ray_n
{
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	bool vertical_hit;
	float distance;
	int wall_hit_content;
} ray_t;

extern ray_t rays[NUM_RAYS];

void normalize_angle(float *angle);
float distance_bn_points(float x1, float y1, float x2, float y2);
void cast_ray(float ray_angle, int column_id);
void cast_all_rays(void);
void render_map_rays(void);
bool is_ray_facing_up(float angle);
bool is_ray_facing_down(float angle);
bool is_ray_facing_left(float angle);
bool is_ray_facing_right(float angle);

#endif
