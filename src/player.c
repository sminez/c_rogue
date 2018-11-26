#include <malloc.h>
#include "player.h"
#include "entity.h"

Player* init_player(int y, int x) {
    Player* p;
    Entity* e;

    p = malloc(sizeof(Player));
    e = entity_new('@', "player", false, 0, 0);

    p->e = e;
    p->hp = PLAYER_HP;
    return p;
}

void player_move(Player* p, int dy, int dx) {
    // TODO: Handle blocking tiles and attacks
    p->e->x += dx;
    p->e->y += dy;
}