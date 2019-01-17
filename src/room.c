#include <malloc.h>
#include <math.h>
#include "libtcod.h"
#include "room.h"


Room* room_new(int x, int y, int w, int h, int id) {
    Room *r;
    r = malloc(sizeof(Room));

    r->x1 = x;
    r->y1 = y;
    r->x2 = x + w;
    r->y2 = y + h;
    r->id = id;
    return r;
}

void room_center(Room *r, int *x, int *y) {
    *x = (r->x1 + r->x2) / 2;
    *y = (r->y1 + r->y2) / 2;
}

double room_distance_to(Room *r, Room *s) {
    int x1, x2, y1, y2;

    room_center(r, &x1, &y1);
    room_center(s, &x2, &y2);
    return sqrt(pow((double)(x1-x2), 2) + pow((double)(y1-y2), 2));
}

void room_random_point(Room *r, int o, int *x, int *y) {
    TCOD_random_t rng;
    rng = TCOD_random_get_instance();

    *x = TCOD_random_get_int(rng, r->x1 + o, r->x2 - o);
    *y = TCOD_random_get_int(rng, r->y1 + o, r->y2 - o);
}

bool room_overlaps_with(Room *r, Room *s) {
    bool xcond, ycond;
    int p = ROOM_PADDING;

    xcond = r->x1-p <= s->x2+p && r->x2+p >= s->x1-p;
    ycond = r->y1-p <= s->y2+p && r->y2+p >= s->y1-p;
    return xcond && ycond;
}

bool room_h_with(Room *r, Room *s) {
    bool left, right;

    left = (r->x2 < s->x1) && (r->x2 < s->x2);
    right = (r->x1 > s->x1) && (r->x1 > s->x2);
    return left || right;
}
