#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>
#include <stdint.h>
#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

#define PI 3.141592625
#define TWO_PI 6.28318530

#define TILE_SIZE 64
#define MINIMAP_SCALE_FACTOR 0.2
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

#define FOV_ANGLE ((60 * PI) / 180)
#define NUM_RAYS WINDOW_WIDTH

#define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

typedef uint32_t color_t;

#endif
