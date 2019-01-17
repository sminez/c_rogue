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
    d->current_floor = 0;

    for (i=0; i < N_FLOORS; i++)
        dungeon_new_floor(d, i);

    dungeon_move_to_floor(d, 0, -1);
    return d;
}

void dungeon_new_floor(Dungeon *d, int k) {
    d->floors[k] = floor_new(d->w, d->h);
}

void dungeon_move_to_floor(Dungeon *d, int to, int from) {
    int x, y;

    x = d->floors[to]->spawn_x;
    y = d->floors[to]->spawn_y;

    if (from >= 0) {
        // If we came from a real floor (from == -1 on game init) then
        // we store the position of the stairs that we came up as the
        // new entry point.
        d->floors[from]->spawn_x = d->player->m->e->x;
        d->floors[from]->spawn_y = d->player->m->e->y;
    }

    entity_set_coords(d->player->m->e, x, y);
    floor_fov_init(d->floors[to]);
    d->current_floor = to;
}
