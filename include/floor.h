#ifndef _CROGUE_FLOOR_H
#define _CROGUE_FLOOR_H

#include <stdbool.h>
#include "room.h"
#include "tile.h"

#define MAX_ROOM_TRIES 1000
#define MIN_ROOM_SIZE 7
#define MAX_ROOM_SIZE 18

typedef struct {
    int w;
    int h;
    int n_rooms;
    Tile** map;
    Room** rooms;
} Floor;

Floor* floor_new(int w, int h);
void floor_carve_room(Floor* f, Room* r);

#endif