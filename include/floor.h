#ifndef _CROGUE_FLOOR_H
#define _CROGUE_FLOOR_H

#include <stdbool.h>
#include "libtcod.h"
#include "room.h"
#include "tile.h"

#define MAX_ROOM_TRIES 2000
#define MIN_ROOM_SIZE 6
#define MAX_ROOM_SIZE 12

typedef struct {
    int w;
    int h;
    int spawn_x;
    int spawn_y;
    int n_rooms;
    TCOD_map_t fov1;
    TCOD_map_t fov2;
    Tile **map;
    Room **rooms;
} Floor;

Floor* floor_new(int w, int h);
void floor_carve_room(Floor *f, Room *r);
void floor_connect(Floor *f);
void floor_connect_rooms(Floor *f, Room *r, Room *s);
void floor_make_corridor(Floor *f, int p1, int p2, int c, bool horizontal);
void floor_fov_init(Floor *f);
void floor_add_exits(Floor *f);

#endif