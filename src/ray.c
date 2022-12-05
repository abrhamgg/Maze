#include "../headers/ray.h"

ray_t rays[NUM_RAYS];

/**
 * normalize_angle - function that keeps player angle between 0 and 360.
 * 
 * @angle: player rotation angle.
 * Return: void
 */

void normalize_angle(float* angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle = TWO_PI + *angle;
	//return (angle);
}

/**
 * distance_bn_points - calculate the distance between points
 * 
 * @x1: x-position-1
 * @y1: y-position-1
 * @x2: x-position-2 
 * @y2: y-position-2
 * 
 * Return: float.
 */
float distance_bn_points(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

/**
 * is_ray_facing_down - checks if the player angle is facing down
 * 
 * @angle: rotation angle 
 * Return: true or false.
 */
bool is_ray_facing_down(float angle)
{
	return angle > 0 && angle < PI;
}

/**
 * is_ray_facing_up - checks if the player angle is facing up
 * 
 * @angle: rotation angle
 * Return: true or false.
 */

bool is_ray_facing_up(float angle)
{
	return !is_ray_facing_down(angle);
}

/**
 * is_ray_facing_right - checks if the player angle is facing right
 * 
 * @angle: rotation angle
 * Return: true or false.
 */

bool is_ray_facing_right(float angle)
{
	return angle < 0.5 * PI || angle > 1.5 * PI;
}

/**
 * is_ray_facing_left - checks if the player angle is facing left
 * 
 * @angle: rotation angle
 * Return: true or false.
 */

bool is_ray_facing_left(float angle)
{
	return !is_ray_facing_right(angle);
}

/**
 * cast_ray - function to cast ray in the map.
 * 
 * @ray_angle: ray angle
 * @column_id: column id
 * Return: void
 */

void cast_ray(float ray_angle, int column_id)
{
	normalize_angle(&ray_angle);
	/*
	########################################
	##### HORIZONTAL WALL INTERSECTION #####
	########################################
	*/

	float x_intercept, y_intercept;
	float x_step, y_step;
	/*HORIZONTAL WALL INTERSECTION*/
	bool found_horiz_wall_hit = false;
	float horiz_wall_hit_x = 0;
	float horiz_wall_hit_y = 0;
	int horiz_wall_content = 0;

	y_intercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += is_ray_facing_down(ray_angle) ? TILE_SIZE : 0;

	x_intercept = player.x + (y_intercept - player.y) / tan(ray_angle);

	y_step = TILE_SIZE;
	y_step *= is_ray_facing_up(ray_angle) ? -1 : 1;

	x_step = TILE_SIZE / tan(ray_angle);
	x_step *= (is_ray_facing_left(ray_angle) && x_step > 0) ? -1 : 1;
	x_step *= (is_ray_facing_right(ray_angle) && x_step < 0) ? -1 : 1;

	float next_horz_touch_x = x_intercept;
	float next_horz_touch_y = y_intercept;
	// Increment x step and y step until we find a wall
	while (is_inside_map(next_horz_touch_x, next_horz_touch_y))
	{
		float x_check = next_horz_touch_x;
		float y_check = next_horz_touch_y + (is_ray_facing_up(ray_angle) ? -1 : 0);
		//fprintf(stderr, "xcheck is %f and y_check is %f\n", y_check, x_check);
		if (has_wall(x_check, y_check))
		{
			horiz_wall_hit_x = next_horz_touch_x;
			horiz_wall_hit_y = next_horz_touch_y;
			horiz_wall_content = get_map_at_pos((int)floor(y_check / TILE_SIZE), (int)floor(x_check / TILE_SIZE));
			found_horiz_wall_hit = true;
			break;
		}
		else
		{
			next_horz_touch_x += x_step;
			next_horz_touch_y += y_step;
		}
	}
	/*
	######################################
	#### VERTICAL WALL INTERSECTION ######
	######################################
	*/
	bool found_vert_wall_hit = false;
	float vert_wall_hit_x = 0;
	float vert_wall_hit_y = 0;
	int vert_wall_content = 0;

	x_intercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += is_ray_facing_right(ray_angle) ? TILE_SIZE : 0;
	
	y_intercept = player.y + (x_intercept - player.x) * tan(ray_angle);
	/*calculate the increment of xstep and ystep*/
	x_step = TILE_SIZE;
	x_step *= is_ray_facing_left(ray_angle) ? -1 : 1;

	y_step = TILE_SIZE * tan(ray_angle);
	y_step *= (is_ray_facing_up(ray_angle) && y_step > 0) ? -1 : 1;
	y_step *= (is_ray_facing_down(ray_angle) && y_step < 0) ? -1 : 1;

	float next_vert_touch_x = x_intercept;
	float next_vert_touch_y = y_intercept;
	while (is_inside_map(next_vert_touch_x, next_vert_touch_y))
	{
		float y_check = next_vert_touch_y;
		float x_check = next_vert_touch_x + (is_ray_facing_left(ray_angle) ? -1 : 0);
		
		if (has_wall(x_check, y_check))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = get_map_at_pos((int)floor(y_check / TILE_SIZE), (int)floor(x_check / TILE_SIZE));
			found_vert_wall_hit = true;
			break;
		}
		else
		{
			next_vert_touch_x += x_step;
			next_vert_touch_y += y_step;
		}
	}

	// calculate both horizontal and vertical distance and choose the closest one
	float horizontal_distance = found_horiz_wall_hit ? distance_bn_points(player.x, player.y, horiz_wall_hit_x, horiz_wall_hit_y) : FLT_MAX;
	float vertical_distance = found_vert_wall_hit ? distance_bn_points(player.x, player.y, vert_wall_hit_x, vert_wall_hit_y) : FLT_MAX;
	if (vertical_distance < horizontal_distance)
	{
		rays[column_id].distance = vertical_distance;
		rays[column_id].wall_hit_x = vert_wall_hit_x;
		rays[column_id].wall_hit_y = vert_wall_hit_y;
		rays[column_id].wall_hit_content = vert_wall_content;
		rays[column_id].vertical_hit = true;
		rays[column_id].ray_angle = ray_angle;
	}
	else
	{
		rays[column_id].distance = horizontal_distance;
		rays[column_id].wall_hit_x = horiz_wall_hit_x;
		rays[column_id].wall_hit_y = horiz_wall_hit_y;
		rays[column_id].wall_hit_content = horiz_wall_content;
		rays[column_id].vertical_hit = false;
		rays[column_id].ray_angle = ray_angle;
	}
}

/**
 * cast_all_rays - function to cast all rays
 * Return: void
 */
void cast_all_rays()
{
	float ray_angle = player.roatation_angle - (FOV_ANGLE / 2);

	for (int i = 0; i < NUM_RAYS; i++)
	{
		cast_ray(ray_angle, i);
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}

/**
 * render_map_rays - function to render casted rays on the map
 * Return: void.
 */

void render_map_rays()
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		draw_line(
			MINIMAP_SCALE_FACTOR *  player.x,
			MINIMAP_SCALE_FACTOR * player.y,
			MINIMAP_SCALE_FACTOR * rays[i].wall_hit_x, 
			MINIMAP_SCALE_FACTOR * rays[i].wall_hit_y,
			0xFF0000FF
		);
	}
}