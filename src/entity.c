#include "entity.h"

Entity* entity_new(char c, char *name, bool blocking, int x, int y) {
    Entity *e = malloc(sizeof(Entity));
    e->c = c;
    e->name = name;
    e->blocking = blocking;
    e->x = x;
    e->y = y;
    return e;
}

void entity_move(Entity *e, int dx, int dy) {
    e->x += dx;
    e->y += dy;
}

void entity_set_coords(Entity *e, int x, int y) {
    e->x = x;
    e->y = y;
}