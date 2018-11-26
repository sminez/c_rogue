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
    char* name;
} Entity;

// Simple linked list of entities
// typedef struct {
//     Entity* e;
//     struct Node* next;
// } Node;

// typedef struct {
//     Node* head;
//     int len;
// } EntityList;


Entity* entity_new(char c, char* name, bool blocking, int x, int y);
void entity_move(Entity* e, int dx, int dy);
void entity_set_coords(Entity* e, int x, int y);

// EntityList* elist_new();
// void elist_insert(EntityList* l, Entity* e);
// void elist_remove(EntityList* l, Entity* e);
// void elist_delete(EntityList* l);

#endif