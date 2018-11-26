#include "entity.h"

Entity* entity_new(char c, char* name, bool blocking, int x, int y) {
    Entity* e = malloc(sizeof(Entity));
    e->c = c;
    e->name = name;
    e->blocking = blocking;
    e->x = x;
    e->y = y;
    return e;
}

void entity_move(Entity* e, int dx, int dy) {
    e->x += dx;
    e->y += dy;
}

EntityList* elist_new() {
    EntityList* e;
    e = malloc(sizeof(EntityList));
    e->head = NULL;
    return e;
}

void elist_insert(EntityList* l, Entity* e) {
    Node* n;
    n = malloc(sizeof(Node));

    n->e = e;
    n->next = l->head;
    l->head = n;
    l->len++;
}

void elist_delete(EntityList* l) {
    Node* current;
    Node* next;
    current = l->head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(l);
}