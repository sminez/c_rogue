#include <malloc.h>
#include "dungeon.h"
#include "floor.h"

Dungeon* dungeon_new(int w, int h, Player* p) {
    Dungeon* d;
    d = malloc(sizeof(Dungeon));
    d->w = w;
    d->h = h;
    d->player = p;
    d->depth = 0;

    dungeon_new_floor(d, 0);
}

void dungeon_new_floor(Dungeon* d, int ix) {
    d->floors[ix] = floor_new(d->w, d->h);
}