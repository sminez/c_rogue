#ifndef _CROGUE_ENTITY_H
#define _CROGUE_ENTITY_H

#include <stdbool.h>
#include <malloc.h>
#include "libtcod/src/libtcod/color.h"

// All game objects other than simple map elements such
// as floors, walls, doors contain an Entity struct to
// store their position and rendering.
typedef struct {
    int x;
    int y;
    char c;
    bool blocking;
    TCOD_color_t fg;
    TCOD_color_t bg;
    char *name;
} Entity;

Entity* entity_new(char c, char *name, bool blocking, int x, int y);
void entity_move(Entity *e, int dx, int dy);
void entity_set_coords(Entity *e, int x, int y);

#endif