#ifndef _CROGUE_TILE_H
#define _CROGUE_TILE_H

#include <stdbool.h>
#include "libtcod/src/libtcod/color.h"

typedef struct {
    bool explored;
    bool blocksVis;
    bool blocksMove;
    char *name;
    char c;
    TCOD_color_t fg;
    TCOD_color_t bg;
    int pathCost;
    int agroCost;
    int agroWeight;
} Tile;

Tile* tile_new();
void tile_wall(Tile* t);
void tile_floor(Tile* t);
void tile_door_closed(Tile* t);
void tile_door_open(Tile* t);
void tile_door_secret(Tile* t);
void tile_stairs_up(Tile* t);
void tile_stairs_down(Tile* t);

#endif