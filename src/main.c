#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include "../headers/defs.h"
#include <math.h>
#include <stdbool.h>
#include "../headers/textures.h"
#include "../headers/graphics.h"
#include "../headers/map.h"
#include "../headers/ray.h"
#include "../headers/player.h"
#include "../headers/wall.h"
#include "../headers/sprite.h"

static bool is_game_running = false;
static int ticks_last_frame = 0;

/*uint32_t* textures[NUM_TEXTURES];*/

/**
 * setup - function that sets up the player properties
 * Return: void.
 */

void setup()
{
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;
	player.width = 5;
	player.height = 5;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.roatation_angle = PI / 2;
	player.walk_speed = 100;
	player.turn_speed = 45 * (PI / 180);
	/*allocate the total amount of memory for the color buffer*/
	/**create a texture with pattern of blue and black lines
	wall_texture = (uint32_t*) malloc(sizeof(uint32_t) * (uint32_t)TEXTURE_WIDTH * (uint32_t)TEXTURE_HEIGHT);
	for (int x = 0; x < TEXTURE_WIDTH; x++)
	{
		for (int y = 0; y < TEXTURE_HEIGHT; y++)
		{
			wall_texture[(TEXTURE_HEIGHT * y) + x] = (x % 8 && y % 8) ? 0xFF0000FF : 0xFF000000;
		}
	}*/
	/*load some textures from the textures.h*/
	load_textures();
}

/**
 * process_input - function that handles events in the game window
 * Return: void.
 */

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			is_game_running = false;
			break;
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_game_running = false;
			if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
				player.walk_direction = +1;
			if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
				player.walk_direction = -1;
			if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
			{
				player.turn_direction = -1;
				//fprintf(stderr, "%d\n",player.turn_direction);
			}
			if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				player.turn_direction = +1;
			break;
		}
		case SDL_KEYUP:
		{
			if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
				player.walk_direction = 0;
			if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
				player.walk_direction = 0;
			if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
			{
				player.turn_direction = 0;
				fprintf(stderr, "%d\n", player.turn_direction);
			}
			if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				player.turn_direction = 0;
			break;
		}
		default:
			break;
	}
}


/**
 * update - function that updates the window by avoiding difference
 * in refresh rate in devices with different resolution.
 * 
 * Return: void.
 */
void update()
{
	int time_to_wait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticks_last_frame);
	if (time_to_wait > 0 && time_to_wait <= FRAME_TIME_LENGTH)
	{
		SDL_Delay(time_to_wait);
	}
	//while (!SDL_TICKS_PASSED( SDL_GetTicks(), ticks_last_frame + FRAME_TIME_LENGTH ));
	float delta_time = (SDL_GetTicks() - ticks_last_frame) / 1000.0f;

	ticks_last_frame = SDL_GetTicks();
	//fprintf(stderr, "%d\n", player.walk_direction);hh
	move_player(delta_time);
	cast_all_rays();
}

/**
 * render - function which is responsible of rendering the window.
 * 
 * Return: void.
 */

void render()
{
	/*
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	*/
	clear_color_buffer(0xFF000000);
	render_wall_3d_projection();
	render_sprite_projection();


	render_map_grid();
	render_map_rays();
	render_map_player();
	render_map_sprites();
	render_color_buffer();
	//SDL_RenderPresent(renderer);
}

/**
 * release_resources - function that releases resources
 * from the memory which are allocated using malloc and the SDL library.
 * 
 * Return: void.
 */
void release_resources()
{
	free_textures();
	destroy_window();
}

/**
 * main - main function which includes every operations and functions.
 * 
 * Return:  
 */

int main(void)
{
	is_game_running = initialize_window();
	setup();
	while (is_game_running)
	{
		process_input();
		update();
		render();
	}
	release_resources();
	return 0;
}
