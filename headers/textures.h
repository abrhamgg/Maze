#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdint.h>
#include "defs.h"
#include "../headers/external_lib/upng.h"
#include <stddef.h>
#include <stdio.h>
#define NUM_TEXTURES 14

extern upng_t* textures[NUM_TEXTURES];

void load_textures(void);
void free_textures(void);

#endif
