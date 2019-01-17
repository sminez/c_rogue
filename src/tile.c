#include <malloc.h>
#include "tile.h"
#include "colors.h"


Tile* tile_new() {
    Tile *t;

    t = malloc(sizeof(Tile));
    t->explored = false;
    return t;
}

void tile_wall(Tile *t) {
    t->blocksVis = true;
    t->blocksMove = true;
    t->tt = wall;
    t->c = '#';
    t->fg = DARK4;
    t->bg = DARK1;
    t->pathCost = -1;
    t->agroCost = 4;
}

void tile_ground(Tile *t) {
    t->blocksVis = false;
    t->blocksMove = false;
    t->tt = ground;
    t->c = '.';
    t->fg = DARK4;
    t->bg = DARK0;
    t->pathCost = 1;
    t->agroCost = 1;
}

void tile_door_closed(Tile *t) {
    t->blocksVis = true;
    t->blocksMove = true;
    t->tt = door_closed;
    t->c = '+';
    t->fg = FADED_BROWN;
    t->bg = DARK0;
    t->pathCost = 2;
    t->agroCost = 2;
}

void tile_door_open(Tile *t) {
    t->blocksVis = false;
    t->blocksMove = false;
    t->tt = door_open;
    t->c = '\'';
    t->fg = FADED_BROWN;
    t->bg = DARK0;
    t->pathCost = 2;
    t->agroCost = 2;
}

void tile_door_secret(Tile *t) {
    t->blocksVis = true;
    t->blocksMove = true;
    t->tt = door_secret;
    t->c = '#';
    t->fg = DARK4;
    t->bg = DARK0;
    t->pathCost = -1;
    t->agroCost = 3;
}

void tile_stairs_up(Tile *t) {
    t->blocksVis = false;
    t->blocksMove = false;
    t->tt = stairs_up;
    t->c = '<';
    t->fg = WHITE;
    t->bg = DARK0;
    t->pathCost = 1;
    t->agroCost = 1;
}

void tile_stairs_down(Tile *t) {
    t->blocksVis = false;
    t->blocksMove = false;
    t->tt = stairs_down;
    t->c = '>';
    t->fg = WHITE;
    t->bg = DARK0;
    t->pathCost = 1;
    t->agroCost = 1;
}
