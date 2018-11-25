#include "tile.h"
#include "colors.h"


void tile_wall(Tile* t) {
    t->blocksVis = true;
    t->blocksMove = true;
    t->name = "wall";
    t->sym = '#';
    t->fg = DARK4;
    t->bg = DARK1;
    t->pathCost = -1;
    t->agroCost = 4;
}

void tile_floor(Tile* t) {
    t->blocksVis = false;
    t->blocksMove = false;
    t->name = "floor";
    t->sym = '.';
    t->fg = DARK4;
    t->bg = DARK0;
    t->pathCost = 1;
    t->agroCost = 1;
}

void tile_door_closed(Tile* t) {
    t->blocksVis = true;
    t->blocksMove = true;
    t->name = "door_closed";
    t->sym = '+';
    t->fg = FADED_BROWN;
    t->bg = DARK0;
    t->pathCost = 2;
    t->agroCost = 2;
}

void tile_door_open(Tile* t) {
    t->blocksVis = false;
    t->blocksMove = false;
    t->name = "door_open";
    t->sym = '\'';
    t->fg = FADED_BROWN;
    t->bg = DARK0;
    t->pathCost = 2;
    t->agroCost = 2;
}

void tile_door_secret(Tile* t) {
    t->blocksVis = true;
    t->blocksMove = true;
    t->name = "door_secret";
    t->sym = '#';
    t->fg = DARK4;
    t->bg = DARK1;
    t->pathCost = -1;
    t->agroCost = 3;
}

void tile_stairs_up(Tile* t) {
    t->blocksVis = false;
    t->blocksMove = false;
    t->name = "stairs_up";
    t->sym = '<';
    t->fg = WHITE;
    t->bg = DARK0;
    t->pathCost = 1;
    t->agroCost = 1;
}

void tile_stairs_down(Tile* t) {
    t->blocksVis = false;
    t->blocksMove = false;
    t->name = "stairs_down";
    t->sym = '>';
    t->fg = WHITE;
    t->bg = DARK0;
    t->pathCost = 1;
    t->agroCost = 1;
}