#include <stdbool.h>
#include <malloc.h>
#include <limits.h>
#include "libtcod.h"
#include "floor.h"
#include "room.h"
#include "tile.h"
#include "mob.h"

Floor* floor_new(int w, int h) {
    int x, y, i, j, n_rooms;
    TCOD_random_t rng;
    bool overlaps;
    Room **rooms;
    Floor *f;
    Room *r;

    rng = TCOD_random_get_instance();
    f = malloc(sizeof(Floor));
    rooms = malloc(sizeof(Room) * MAX_ROOM_TRIES);

    f->w = w;
    f->h = h;
    f->n_mobs = f->n_rooms = 0;
    f->spawn_x = f->spawn_y = 0;

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
    floor_connect(f);
    floor_add_exits(f);
    floor_add_mobs(f, 0);
    return f;
}

void floor_carve_room(Floor *f, Room *r) {
    int x, y;

    for (x=r->x1+1; x < r->x2; x++)
        for (y=r->y1+1; y < r->y2; y++)
            tile_ground(&f->map[y][x]);
}

void floor_connect(Floor *f) {
    int i, j, min_i, min_j, N, min, n_connected;
    Room *r, *s;
    N = f->n_rooms;
    double a_mat[N][N];
    bool connected[N];

    n_connected = 1;
    for (i=1; i < N; i++)
        connected[i] = false;
    connected[0] = true;

    // Find the full adjacency matrix
    for (i=0; i < N; i++)
        for (j=0; j < N; j++)
            a_mat[i][j] = room_distance_to(
                f->rooms[i], f->rooms[j]
            );

    while (n_connected < N) {
        for (i=0; i < N; i++) {
            if (!connected[i])
                continue;

            min = INT_MAX;
            for (j=0; j < N; j++) {
                if (i != j && !connected[j] && a_mat[i][j] < min) {
                    min = a_mat[i][j];
                    min_i = i;
                    min_j = j;
                    r = f->rooms[i];
                    s = f->rooms[j];
                }
            }
        }
        floor_connect_rooms(f, r, s);
        connected[min_i] = connected[min_j] = true;
        n_connected++;
    }
    // Add in some additional connections
    // TODO
}

void floor_connect_rooms(Floor *f, Room *r, Room *s) {
    int x1, x2, y1, y2, e1, e2, m1, m2, k;
    bool horizontal;
    TCOD_random_t rng;

    rng = TCOD_random_get_instance();
    room_random_point(r, 3, &x1, &y1);
    room_random_point(s, 3, &x2, &y2);
    horizontal = room_h_with(r, s);

    if (horizontal) {
        k = TCOD_random_get_int(rng, MIN(x1, x2), MAX(x1, x2));
        e1 = x1; e2 = x2; m1 = y1; m2 = y2;
    } else {
        k = TCOD_random_get_int(rng, MIN(y1, y2), MAX(y1, y2));
        e1 = y1; e2 = y2; m1 = x1; m2 = x2;
    }

    // Make an S-bend corridor
    floor_make_corridor(f, e1, k, m1, horizontal);
    floor_make_corridor(f, e2, k, m2, horizontal);
    floor_make_corridor(f, m1, m2, k, !horizontal);
}

void floor_make_corridor(Floor *f, int p1, int p2, int c, bool horizontal) {
    int a, b, i;

    a = MIN(p1, p2);
    b = MAX(p1, p2);

    if (horizontal)
        for (i=a; i<=b; i++) {
            tile_ground(&f->map[c][i]);
        }
    else
        for (i=a; i<=b; i++) {
            tile_ground(&f->map[i][c]);
        }
}

void floor_add_exits(Floor *f) {
    int x, y;
    Room *r;

    r = f->rooms[0];
    room_random_point(r, 2, &x, &y);
    tile_stairs_up(&f->map[y][x]);
    // The stairs up to the next level are the default entry point.
    f->spawn_x = x; f->spawn_y = y;

    r = f->rooms[f->n_rooms-1];
    room_random_point(r, 2, &x, &y);
    tile_stairs_down(&f->map[y][x]);
}

void floor_fov_init(Floor *f) {
    int x, y;
    Tile t;
    TCOD_map_t m, n;

    m = TCOD_map_new(f->w, f->h);
    n = TCOD_map_new(f->w, f->h);

    for (x=0; x < f->w; x++)
        for (y=0; y < f->h; y++) {
            t = f->map[y][x];
            TCOD_map_set_properties(m, x, y, !t.blocksVis, !t.blocksMove);
        }

    TCOD_map_copy(m, n);
    f->fov1 = m;
    f->fov2 = n;
}

void floor_add_mobs(Floor *f, int depth) {
    int i, x, y;
    Room *r;
    Mob *m;
    struct Mob **mobs;

    // TODO: Compute number/type of mobs differently for each level
    f->n_mobs = f->n_rooms;
    mobs = malloc(sizeof(Mob) * f->n_mobs);

    for (i=0; i < f->n_rooms; i++) {
        m = mob_new_goblin(depth);
        r = f->rooms[i];
        room_random_point(r, 2, &x, &y);
        entity_set_coords(m->e, x, y);
        mobs[i] = m;
    }

    f->mobs = mobs;
}