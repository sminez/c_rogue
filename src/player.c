#include <malloc.h>
#include <math.h>
#include "libtcod.h"
#include "player.h"
#include "entity.h"
#include "floor.h"
#include "colors.h"

Player* init_player(int y, int x) {
    Player* p;
    Entity* e;

    p = malloc(sizeof(Player));
    e = entity_new('@', "player", false, 0, 0);

    p->e = e;
    p->e->fg = LIGHT0;
    p->STR = PLAYER_BASE_STR;
    p->DEX = PLAYER_BASE_DEX;
    p->VIT = PLAYER_BASE_VIT;
    p->INT = PLAYER_BASE_INT;
    p->hp = PLAYER_BASE_HP;
    p->hp_max = PLAYER_BASE_HP;
    p->xp = 0;
    p->xp_next = 50;
    p->level = 1;
    p->gold = 0;
    p->vision1 = PLAYER_BASE_VISION1;
    p->vision2 = PLAYER_BASE_VISION2;
    return p;
}

void player_move(Player *p, Floor *f, int dy, int dx) {
    int x, y;
    x = p->e->x + dx;
    y = p->e->y + dy;

    if (!f->map[y][x].blocksMove)
        entity_move(p->e, dx, dy);
}

void player_color_from_health(Player *p) {
    double perc;
    perc = (double)p->hp / (double)p->hp_max;

    if (perc > 0.75) {
        p->e->fg = LIGHT0;
    } else if (perc > 0.5) {
        p->e->fg = BRIGHT_YELLOW;
    } else if (perc > 0.25) {
        p->e->fg = BRIGHT_ORANGE;
    } else {
        p->e->fg = BRIGHT_RED;
    }
}

void player_level_up(Player *p) {
    int h;
    TCOD_random_t rng;

    p->xp -= p->xp_next;
    p->xp_next = floor(p->xp_next * PLAYER_XP_MUL);
    p->level += 1;

    // Increase HP
    rng = TCOD_random_get_instance();
    h = TCOD_random_get_int(rng, 1, 10) + p->VIT;
    p->hp_max += h;
    p->hp += h;

    // Increase a stat
    switch(TCOD_random_get_int(rng, 1, 4)) {
        case 1:
            p->STR += 1;
            break;
        case 2:
            p->DEX += 1;
            break;
        case 3:
            p->VIT += 1;
            break;
        case 4:
            p->INT += 1;
            break;
    }
}