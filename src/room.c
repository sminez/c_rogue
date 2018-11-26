#include <malloc.h>
#include "libtcod.h"
#include "room.h"


Room* room_new(int x, int y, int w, int h, int id) {
    Room* r;
    r = malloc(sizeof(Room));

    r->x1 = x;
    r->y1 = y;
    r->x2 = x + w;
    r->y2 = y + h;
    r->id = id;
    return r;
}

void room_center(Room* r, int* x, int* y) {
    *x = (r->x1 + r->x2) / 2;
    *y = (r->y1 + r->y2) / 2;
}

void room_random_point(Room* r, int offset, int* x, int* y) {
    TCOD_random_t rng;
    rng = TCOD_random_get_instance();

    *x = r->x1 + TCOD_random_get_int(rng, 0, r->x2 - r->x1 + 1);
    *y = r->y1 + TCOD_random_get_int(rng, 0, r->y2 - r->y1 + 1);
}

bool room_overlaps_with(Room* r, Room* s) {
    bool xcond, ycond;
    int p = ROOM_PADDING;
    xcond = r->x1-p <= s->x2+p && r->x2+p >= s->x1-p;
    ycond = r->y1-p <= s->y2+p && r->y2+p >= s->y1-p;
    return xcond && ycond;
}

bool room_h_with(Room* r, Room* s) {
    return r->x2 < s->x1 && r->x2 < s->x2 ||
           r->x1 > s->x1 && r->x1 > s->x2;
}