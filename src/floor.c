#include <malloc.h>
#include "floor.h"
#include "tile.h"

Floor* floor_new(int w, int h) {
    int y, x;
    Floor* f;
    f = malloc(sizeof(Floor));

    f->w = w;
    f->h = h;

    // Block fill the map with walls
    f->map = malloc(sizeof(Tile) * h);
    for (y=0; y < h; y++) {
        f->map[y] = malloc(sizeof(Tile) * w);
        for (x=0; x < w; x++) {
            tile_wall(&f->map[y][x]);
        }
    }
    return f;
}