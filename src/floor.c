#include <stdbool.h>
#include <malloc.h>
#include "libtcod.h"
#include "floor.h"
#include "room.h"
#include "tile.h"

Floor* floor_new(int w, int h) {
    int x, y, i, j, n_rooms;
    TCOD_random_t rng;
    bool overlaps;
    Room** rooms;
    Floor* f;
    Room* r;

    rng = TCOD_random_get_instance();
    f = malloc(sizeof(Floor));
    rooms = malloc(sizeof(Room) * MAX_ROOM_TRIES);

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

    n_rooms = 0;
    for (i=0; i < MAX_ROOM_TRIES; i++) {
        w = TCOD_random_get_int(rng, MIN_ROOM_SIZE, MAX_ROOM_SIZE);
        h = TCOD_random_get_int(rng, MIN_ROOM_SIZE, MAX_ROOM_SIZE);
        x = TCOD_random_get_int(rng, 0, f->w - w - 1);
        y = TCOD_random_get_int(rng, 0, f->h - h - 1);
        r = room_new(x, y, w, h, n_rooms);

        overlaps = false;
        for (j=0; j < n_rooms; j++) {
            if (room_overlaps_with(r, rooms[j])) {
                overlaps = true;
                break;
            }
        }
        if (!overlaps) {
            rooms[n_rooms] = r;
            floor_carve_room(f, r);
            n_rooms++;
        }
    }

    rooms = realloc(rooms, sizeof(Room) * n_rooms);
    f->rooms = rooms;
    f->n_rooms = n_rooms;
    return f;
}

void floor_carve_room(Floor* f, Room* r) {
    int x, y;

    for (x=r->x1+1; x < r->x2; x++)
        for (y=r->y1+1; y < r->y2; y++)
            tile_floor(&f->map[y][x]);

    // TODO: keep list of rooms
}