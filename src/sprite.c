#include "../headers/sprite.h"
#define NUM_SPRITES 5
static sprite_t sprites[NUM_SPRITES] = {
    {.x = 640, .y = 630, .texture = 9},
    {.x = 620, .y = 600, .texture = 9},
    {.x = 250, .y = 600, .texture = 11},
    {.x = 300, .y = 340, .texture = 12},
    {.x = 90, .y = 100, .texture = 13}
};

void render_map_sprites()
{
    for (int i = 0; i < NUM_SPRITES; i++)
    {
        draw_rect(sprites[i].x * MINIMAP_SCALE_FACTOR, 
            sprites[i].y * MINIMAP_SCALE_FACTOR,
            2, 2,
            sprites[i].visible ? 0xFF00FFFF : 0xFF0000);
    }
}

void render_sprite_projection()
{
    sprite_t visible_sprites[NUM_SPRITES];
    int num_visible_sprites = 0;

    for (int i = 0; i < NUM_SPRITES; i++)
    {
        float angle_sprite_player = player.roatation_angle - atan2(sprites[i].y - player.y, sprites[i].x - player.x);

        if (angle_sprite_player > PI)
            angle_sprite_player -= TWO_PI;
        if (angle_sprite_player < -PI)
            angle_sprite_player += TWO_PI;
        angle_sprite_player = fabs(angle_sprite_player);

        // if sprite angle is less than half the FOV plus a small margin
        const float EPISLON = 0.2;
        if (angle_sprite_player < (FOV_ANGLE / 2) + EPISLON)
        {
            sprites[i].visible = true;
            sprites[i].angle = angle_sprite_player;
            sprites[i].distance = distance_bn_points(sprites[i].x, sprites[i].y, player.x, player.y);
            //fprintf(stderr, " Visible %d\n", sprites[i].visible);
            visible_sprites[num_visible_sprites] = sprites[i];
            num_visible_sprites++;
        }
        else
        {
            //fprintf(stderr, "Not Visible %d\n", sprites[i].visible);
            sprites[i].visible = false;
        }
    }

    for (int i = 0; i < num_visible_sprites - 1; i++)
    {
        for (int j = i + 1; j < num_visible_sprites; j++)
        {
            if (visible_sprites[i].distance < visible_sprites[j].distance)
            {
                sprite_t temp = visible_sprites[i];
                visible_sprites[i] = visible_sprites[j];
                visible_sprites[j] = temp;
            }
        }
    }

    for (int i = 0; i < num_visible_sprites; i++)
    {
        sprite_t sprite= visible_sprites[i];

        // calcaulate the perpendicular distance to avoid fishbowl distortion
        float perp_distance = sprite.distance * cos(sprite.angle);
        // calculate sprite projected height
        float sprite_height = (TILE_SIZE / perp_distance) * DIST_PROJ_PLANE;
        float sprite_width = sprite_height;

        // calculate sprite top y value and bottom y value
        float sprite_top_y = (WINDOW_HEIGHT / 2) - (sprite_height / 2);
        sprite_top_y =  sprite_top_y < 0 ? 0 : sprite_top_y;

        float sprite_bottom_y = (WINDOW_HEIGHT / 2) + (sprite_height / 2);
        sprite_bottom_y = sprite_bottom_y > WINDOW_HEIGHT ? WINDOW_HEIGHT : sprite_bottom_y;

        // sprite_left x
        float sprite_angle = atan2(sprite.y - player.y, sprite.x - player.x) - player.roatation_angle;
        float sprite_pos_x = tan(sprite_angle) * DIST_PROJ_PLANE;

        float sprite_left_x = (WINDOW_WIDTH / 2) + sprite_pos_x - (sprite_width / 2);

        float sprite_right_x = sprite_left_x + sprite_width;

        int texture_width = upng_get_width(textures[sprite.texture]);
        int texture_height = upng_get_height(textures[sprite.texture]);

        for (int x = sprite_left_x; x < sprite_right_x; x++)
        {
            float texel_width = (texture_width / sprite_width);
            int texture_offset_x = (x - sprite_left_x) * texel_width;
            for (int y = sprite_top_y; y < sprite_bottom_y; y++)
            {
                int distance_from_top = y + (sprite_height / 2) - (WINDOW_HEIGHT / 2);
                int texture_offset_y = distance_from_top * (texture_height / sprite_height);
                if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
                {
                    u_int32_t* sprite_texture_buffer = (u_int32_t*) upng_get_buffer(textures[sprite.texture]);
                    u_int32_t texel_color = sprite_texture_buffer[(texture_width * texture_offset_y) + texture_offset_x];
                    if (texel_color != 0xFFFF00FF && sprite.distance < rays[x].distance)
                        draw_pixel(x, y, texel_color);
                }
            }
        }
    }
}