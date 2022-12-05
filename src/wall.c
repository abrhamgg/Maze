#include "../headers/wall.h"

/**
 * change_color - accepts the address of a texture color and changes the color intensity of a texture.
 * 
 * @color: pointer to the color of texture.
 * @factor: factor to change the intensity.
 * 
 * Return: void.
 */
void change_color(uint32_t* color, float factor)
{
    uint32_t a = (*color & 0XFF000000);
    uint32_t r = (*color & 0x00FF0000) * factor;
    uint32_t g = (*color & 0x0000FF00) * factor;
    uint32_t b = (*color & 0x000000FF) * factor;

    *color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

/**
 * render_wall_3d_projecttion - function that renders a wall in the window.
 * 
 * Return: void.
 */

void render_wall_3d_projection()
{
	for (int i = 0; i < NUM_RAYS; i++)
	{
		float perp_distance = rays[i].distance * cos(rays[i].ray_angle - player.roatation_angle);
		float distance_of_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		float wall_height = (TILE_SIZE / perp_distance) * distance_of_projection_plane;


		int wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

		int wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_bottom_pixel;

		/*render the wall*/
		int texture_offset_x;
		if (rays[i].vertical_hit)
		{
			texture_offset_x = (int)rays[i].wall_hit_y % TILE_SIZE;
		}
		else
		{
			texture_offset_x = (int)rays[i].wall_hit_x % TILE_SIZE;
		}
		int tex_num = rays[i].wall_hit_content - 1;
		// Query texture width and height from the upng

		int texture_width = upng_get_width(textures[tex_num]);
		int texture_height = upng_get_height(textures[tex_num]);

		for (int y = wall_top_pixel; y < wall_bottom_pixel; y++)
		{
			int distance_from_top = y + (wall_height / 2) - (WINDOW_HEIGHT / 2);
			int texture_offset_y = distance_from_top * ((float)texture_height / wall_height);
			//set the color of the wall based on the color of the texture
			uint32_t* wall_texture_buffer = (uint32_t*) upng_get_buffer(textures[tex_num]);
			uint32_t texel_color = wall_texture_buffer[(texture_width * texture_offset_y) + texture_offset_x];
            if (rays[i].vertical_hit)
            {
                change_color(&texel_color, 0.6);
            }
			draw_pixel(i, y, texel_color);
			//color_buffer[(WINDOW_WIDTH * y) + i] = texel_color;
			//color_buffer[(WINDOW_WIDTH * y) + i] = rays[i].vertical_hit ? 0XFFFFFFFF : 0xFFCCCCCC;
		}
		/*render the ceiling*/
		for (int j = 0; j < wall_top_pixel; j++)
		{
			draw_pixel(i, j, 0XFF87CEEB);
		}
		/*render the floor*/
		for (int k = wall_bottom_pixel; k < WINDOW_HEIGHT; k++)
		{
			draw_pixel(i, k, 0XFF9B7653);
			//color_buffer[(WINDOW_WIDTH * k) + i] = 0XFF9B7653;
		}
	}
}