#include "../headers/map.h"

static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1},
    {1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 2, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5}
};

/**
 * has_wall - function to check if there's a wall in a given point
 * 
 * @x: x-position
 * @y: y-position
 * 
 * Return: true if there is a wall 
 */
bool has_wall(float x, float y)
{
	if (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE)
	{
		return (true);
	}
	int map_index_x = floor(x / TILE_SIZE);
	int map_index_y = floor(y / TILE_SIZE);
	
	if (map[map_index_y][map_index_x] != 0)
		return (true);
	return (false);
}

/**
 * is_inside_map - function that checks if the given points are inside a map
 * 
 * @x: 
 * @y: 
 * Return: if location is inside a map return true else false.
 */

bool is_inside_map(float x, float y)
{
    if (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE)
    {
        return (true);
    }
    return (false);
}

/**
 * get_map_at_pos - function that return the map grid index of a given point.
 * 
 * @i: value-1 
 * @j: value-2 
 * Return: map index.
 */
int get_map_at_pos(int i, int j)
{
    return map[i][j];
}

/**
 * render_map_grid - function which renders the 2d map grid.
 * 
 * Return: void.
 */
void render_map_grid()
{
    int tile_x, tile_y;
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			tile_x = j * TILE_SIZE;
			tile_y = i * TILE_SIZE;
			u_int32_t tile_color = map[i][j] != 0 ? 0xFFFFFFFF : 0xFF000000;
			draw_rect(
                tile_x * MINIMAP_SCALE_FACTOR,
                tile_y * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                TILE_SIZE * MINIMAP_SCALE_FACTOR,
                tile_color
            );
        }
	}
}