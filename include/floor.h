#ifndef _CROGUE_FLOOR_H
#define _CROGUE_FLOOR_H

#include <stdbool.h>
#include "room.h"
#include "tile.h"

#define MAX_ROOM_TRIES 500
#define MIN_ROOM_SIZE 7
#define MAX_ROOM_SIZE 18

typedef struct {
    int w;
    int h;
    int n_rooms;
    Tile **map;
    Room **rooms;
} Floor;

Floor* floor_new(int w, int h);
void floor_carve_room(Floor *f, Room *r);
void floor_connect(Floor *f);
void floor_connect_rooms(Floor *f, Room *r, Room *s);
void floor_make_corridor(Floor *f, int p1, int p2, int c, bool horizontal);

#endif