#include <malloc.h>
#include "player.h"
#include "entity.h"
#include "floor.h"

Player* init_player(int y, int x) {
    Player* p;
    Entity* e;

    p = malloc(sizeof(Player));
    e = entity_new('@', "player", false, 0, 0);

    p->e = e;
    p->hp = PLAYER_BASE_HP;
    p->vision = PLAYER_BASE_VISION;
    return p;
}

void player_move(Player* p, Floor* f, int dy, int dx) {
    int x, y;
    x = p->e->x + dx;
    y = p->e->y + dy;

    if (!f->map[y][x].blocksMove)
        entity_move(p->e, dx, dy);
}