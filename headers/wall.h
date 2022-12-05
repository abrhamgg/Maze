#ifndef WALL_H
#define WALL_H

#include "ray.h"
#include "player.h"
#include "defs.h"
#include "graphics.h"
#include "textures.h"
#include "math.h"
void render_wall_3d_projection(void);
void change_color(uint32_t *color, float factor);

#endif
