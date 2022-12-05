#include "../headers/textures.h"
#include <stddef.h>
#include <stdio.h>


static const char* texture_file_name[NUM_TEXTURES] = {
    "./images/redbrick.png",
    "./images/purplestone.png",
    "./images/mossystone.png",
    "./images/graystone.png",
    "./images/colorstone.png",
    "./images/bluestone.png",
    "./images/wood.png",
    "./images/eagle.png",
    "./images/pikuma.png",
    "./images/barrel.png",
    "./images/light.png",
    "./images/table.png",
    "./images/guard.png",
    "./images/armor.png"
};

/**
 * load_textures - function to load a texture in to textures array using the upng library.
 * 
 * Return: void.
 */
void load_textures()
{
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        upng_t* upng;
        upng = upng_new_from_file(texture_file_name[i]);
        if (upng != NULL)
        {
            upng_decode(upng);
            if (upng_get_error(upng) == UPNG_EOK)
            {
                textures[i] = upng;
            }
            else
            {
                printf("Error decoding texture\n");
            }
        }
        else
        {
            printf("Error Loading texture%s\n", texture_file_name[i]);
        }
    }
}

/**
 * free_textures - frees allocated texture in memory using upng library.
 * 
 * Return: void
 */
void free_textures()
{
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        upng_free(textures[i]);
    }
}