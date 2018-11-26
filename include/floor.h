#ifndef _CROGUE_FLOOR_H
#define _CROGUE_FLOOR_H

#include <stdbool.h>
#include "room.h"
#include "tile.h"

#define MAX_ROOM_TRIES 1000
#define MIN_ROOM_SIZE 7
#define MAX_ROOM_SIZE 14

typedef struct {
    int w;
    int h;
    Tile** map;
} Floor;

Floor* floor_new(int w, int h);

#endif