#include <malloc.h>
#include <math.h>
#include "libtcod.h"
#include "player.h"
#include "entity.h"
#include "floor.h"
#include "colors.h"
#include "mob.h"

Player* init_player(int y, int x) {
    Player *p;
    Mob *m;

    p = malloc(sizeof(Player));
    m = mob_new(
        '@', "Player", LIGHT0, PLAYER_BASE_PHY, PLAYER_BASE_DEX,
        PLAYER_BASE_VIT, PLAYER_BASE_MND, PLAYER_BASE_HP, 0
    );

    p->m = m;
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
    x = p->m->e->x + dx;
    y = p->m->e->y + dy;

    if (!f->map[y][x].blocksMove)
        entity_move(p->m->e, dx, dy);
}

void player_color_from_health(Player *p) {
    double perc;
    perc = (double)p->m->hp / (double)p->m->hp_max;

    if (perc > 0.75) {
        p->m->e->fg = LIGHT0;
    } else if (perc > 0.5) {
        p->m->e->fg = BRIGHT_YELLOW;
    } else if (perc > 0.25) {
        p->m->e->fg = BRIGHT_ORANGE;
    } else {
        p->m->e->fg = BRIGHT_RED;
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
    h = TCOD_random_get_int(rng, 1, 10) + p->m->VIT;
    p->m->hp_max += h;
    p->m->hp += h;

    // Increase a stat
    switch(TCOD_random_get_int(rng, 1, 4)) {
        case 1:
            p->m->PHY += 1;
            break;
        case 2:
            p->m->DEX += 1;
            break;
        case 3:
            p->m->VIT += 1;
            break;
        case 4:
            p->m->MND += 1;
            break;
    }
}