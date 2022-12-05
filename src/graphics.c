#include "../headers/graphics.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static uint32_t *color_buffer = NULL;
static SDL_Texture *color_buffer_texture;

/**
 * initialize_window - displays and render window in the screen.
 *
 * Return: true if window is created without any errors
 */
bool initialize_window(void)
{
	int full_screen_width;
	int full_screen_height;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializng SDL\n");
		return (false);
	}
	SDL_DisplayMode display_mode;

	SDL_GetCurrentDisplayMode(0, &display_mode);
	full_screen_width = display_mode.w;
	full_screen_height = display_mode.h;
	window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Error Creating SDL Window\n");
		return (false);
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error Rendering Window");
		return (false);
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	color_buffer = (uint32_t *) malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
	/*Create an SDL Texture to display a color buffer*/
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING,
		WINDOW_WIDTH,
		WINDOW_HEIGHT
	);
	return (true);
}

/**
 * destroy_window - frees allocated memory using malloc and by SDL library.
 * Return: void.
 */

void destroy_window(void)
{
	free(color_buffer);
	SDL_DestroyTexture(color_buffer_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

/**
 * clear_color_buffer - function that sets the color buffer with given color values values
 *
 * @color: hexadeciaml rgb value
 * Return: void 
 */
void clear_color_buffer(uint32_t color)
{
	for (int x = 0; x < WINDOW_WIDTH * WINDOW_HEIGHT; x++)
	{
		color_buffer[x] = color;
	}
}

/**
 * render_color_buffer - updates a texture with a color buffer
 *
 * Return: void.
 */
void render_color_buffer(void)
{
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(WINDOW_WIDTH * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

/**
 * draw_pixel - function to draw a pixel at given position.
 *
 * @x: x-position
 * @y: y-position
 * @color: hexadecimal color value.
 * Return: void.
 */

void draw_pixel(int x, int y, uint32_t color)
{
	color_buffer[(WINDOW_WIDTH * y) + x] = color;
}

/**
 * draw_rect - function to draw a rectangle.
 *
 * @x: x-position
 * @y: y-position
 * @width: width of rectangle
 * @height: height of rectangle
 * @color: hexadecimal color value
 *
 * Return: void.
 */

void draw_rect(int x, int y, int width, int height, u_int32_t color)
{
	for (int i = x; i <= (x + width); i++)
	{
		for (int j = y; j <= (y + height); j++)
		{
			draw_pixel(i, j, color);
		}
	}
}

/**
 * draw_line - function to draw a line in the map.
 *
 * @x0: x-position.
 * @y0: y-position
 * @x1: x1-position
 * @y1: y1-position
 * @color: hexadecimal color value.
 *
 * Return: void.
 */
void draw_line(int x0, int y0, int x1, int y1, uint32_t color)
{
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);

	int long_side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

	float x_inc = delta_x / (float)long_side_length;
	float y_inc = delta_y / (float)long_side_length;

	float current_x = x0;
	float current_y = y0;

	for (int i = 0; i < long_side_length; i++)
	{
		draw_pixel(round(current_x), round(current_y), color);

		current_x += x_inc;
		current_y += y_inc;
	}
}
