#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "defs.h"

bool initialize_window(void);
void destroy_window(void);
void clear_color_buffer(uint32_t color);
void render_color_buffer(void);
void draw_pixel(int x, int y, uint32_t color);
void draw_rect(int x, int y, int width, int height, u_int32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);

#endif
