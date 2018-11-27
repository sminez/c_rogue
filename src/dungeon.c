#include <malloc.h>
#include "dungeon.h"
#include "entity.h"
#include "floor.h"

Dungeon* dungeon_new(int w, int h, Player *p) {
    Dungeon *d;
    int i;
    d = malloc(sizeof(Dungeon));
    d->w = w;
    d->h = h;
    d->player = p;
    d->currentFloor = 0;

    for (i=0; i < N_FLOORS; i++)
        dungeon_new_floor(d, i);

    dungeon_move_to_floor(d, 0);
    return d;
}

void dungeon_new_floor(Dungeon *d, int k) {
    d->floors[k] = floor_new(d->w, d->h);
}

void dungeon_move_to_floor(Dungeon *d, int k) {
    int x, y;

    room_center(d->floors[k]->rooms[0], &x, &y);
    entity_set_coords(d->player->e, x, y);
    d->currentFloor = k;
}