#include "../headers/player.h"

player_t player = {
    .x = WINDOW_WIDTH / 2,
	.y = WINDOW_HEIGHT / 2,
	.width = 5,
	.height = 5,
	.turn_direction = 0,
	.walk_direction = 0,
	.roatation_angle = PI / 2,
	.walk_speed = 100,
	.turn_speed = 45 * (PI / 180)
};

/**
 * move_player - function to move the player inside the map.
 * 
 * @delta_time: varibale to normalize delta time.
 * Return: void.
 */

void move_player(float delta_time)
{
	player.roatation_angle += player.turn_direction * player.turn_speed * delta_time;
	normalize_angle(&player.roatation_angle);
	float move_step = player.walk_direction * player.walk_speed * delta_time;

	float new_player_x = player.x + cos(player.roatation_angle) * move_step;
	float new_player_y = player.y + sin(player.roatation_angle) * move_step;
	if (!has_wall(new_player_x, new_player_y))
	{
		player.x = new_player_x;
		player.y = new_player_y;
	}
}

/**
 * render_map_player - function to render the player inside the map
 * 
 * Return: void.
 */
void render_map_player()
{
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	draw_rect(player.x * MINIMAP_SCALE_FACTOR, player.y * MINIMAP_SCALE_FACTOR, player.width * MINIMAP_SCALE_FACTOR, player.height * MINIMAP_SCALE_FACTOR, 0xFFFFFFFF);
	//SDL_RenderFillRect(renderer, &player_rect);
    /*
	SDL_RenderDrawLine(renderer, player.x * MINIMAP_SCALE_FACTOR, player.y * MINIMAP_SCALE_FACTOR,
		MINIMAP_SCALE_FACTOR * player.x + cos(player.roatation_angle) * 40,
		MINIMAP_SCALE_FACTOR * player.y + sin(player.roatation_angle) * 40
	);*/
}
