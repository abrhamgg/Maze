#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "defs.h"
#include "graphics.h"
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
bool has_wall(float x, float y);
void render_map_grid(void);
int get_map_at_pos(int i, int j);
bool is_inside_map(float x, float y);

#endif
