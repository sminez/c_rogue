#include <stdlib.h>
#include "room.h"


Room* new_room(int x, int y, int w, int h) {
    Room* r = malloc(sizeof(Room));
    r->x1 = x;
    r->y1 = y;
    r->x2 = x + w;
    r->y2 = y + h;
    return r;
}

int* room_center(Room* r) {
    int* c;
    c = malloc(sizeof(int) * 2);

    c[0] = (r->x1 + r->x2) / 2;
    c[1] = (r->y1 + r->y2) / 2;
    return c;
}

int* room_random_point(Room* r, int offset) {
    int* p;
    p = malloc(sizeof(int) * 2);

    p[0] = r->x1 + rand() / (RAND_MAX / (r->x2 - r->x1 + 1) + 1);
    p[1] = r->y1 + rand() / (RAND_MAX / (r->y2 - r->y1 + 1) + 1);
    return p;
}

bool room_overlaps_with(Room* r, Room* s) {
    bool xcond, ycond;
    xcond = r->x1 <= s->x2 && r->x2 >= s->x1;
    ycond = r->y1 <= s->y2 && r->y2 >= s->y1;
    return xcond && ycond;
}

bool room_h_with(Room* r, Room* s) {
    return r->x2 < s->x1 && r->x2 < s->x2 ||
           r->x1 > s->x1 && r->x1 > s->x2;
}