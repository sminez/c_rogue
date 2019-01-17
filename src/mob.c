#include <stdbool.h>
#include <stdio.h>
#include "libtcod.h"
#include "colors.h"
#include "render.h"
#include "entity.h"
#include "mob.h"

Mob* mob_new(
    char c, char *name, TCOD_color_t fg,
    int PHY, int DEX, int VIT, int MND, int hp,
    int aggro_range
) {
    Entity *e;
    Mob *m;

    m = malloc(sizeof(Mob));
    e = entity_new(c, name, true, 0, 0);

    m->e = e;
    m->e->fg = fg;
    m->PHY = PHY;
    m->DEX = DEX;
    m->VIT = VIT;
    m->MND = MND;
    m->hp = hp;
    m->hp_max = hp;
    m->aggro_range = aggro_range;
    m->alive = true;
    m->asleep = false;
    m->stunned = false;
    m->confused = false;
    m->frightened = false;

    // TODO: AI
    // TODO: Equipment
    return m;
}

// Helpers
// void mob_equip(Mob *m, Floor *f, Item *i, Slot s);
// int mob_get_equipment_total(Mob *m, Attr a);

int mob_get_dr(Mob *m) {
    int d;
    d = 0;

    // TODO: Add in equipment & skill effects
    return d;
}

int mob_get_ev(Mob *m) {
    int e;
    e = 20 + m->DEX;

    return e;
}

// D100 based
int mob_skill_check(Mob *m, Skill s, int modifier) {
    TCOD_random_t rng;
    rng = TCOD_random_get_instance();

    switch (s) {
        case Phy:
            modifier += m->PHY;
            break;
        case Dex:
            modifier += m->DEX;
            break;
        case Vit:
            modifier += m->VIT;
            break;
        case Mnd:
            modifier += m->MND;
            break;
    }
    return TCOD_random_get_int(rng, 1, 100) + modifier;
}

// FIXME: very simplistic at the moment
struct Message* mob_act(Mob*m, Floor *f) {
    int dx, dy;
    TCOD_random_t rng;

    rng = TCOD_random_get_instance();
    dx = dy = 0;

    if (!m->alive)
        return NULL;

    if (TCOD_random_get_int(rng, 0, 1) == 1) {
        dx = TCOD_random_get_int(rng, -1, 1);
        dy = TCOD_random_get_int(rng, -1, 1);
    }

    return mob_move_or_attack(m, f, dx, dy);
}

struct Message* mob_attack(Mob *m, Mob *t) {
    int damage;

    // TODO: calculate damage better
    damage = m->PHY;
    if (mob_skill_check(m, Phy, -mob_get_ev(t)) > 0)
        return mob_take_damage(t, damage);

    return NULL;
}

struct Message* mob_die(Mob *m) {
    char msg[50];
    sprintf(msg, "%s died!", m->e->name);
    return message_new(msg, BRIGHT_RED);
}

struct Message* mob_heal(Mob *m, int amount) {
    char msg[50];

    m->hp += amount;
    if (m->hp > m->hp_max)
        m->hp = m->hp_max;

    sprintf(msg, "%s healed %d hp", m->e->name, amount);
    return message_new(msg, BRIGHT_GREEN);
}

struct Message* mob_move_or_attack(Mob *m, Floor *f, int dy, int dx) {
    int x, y, i;
    Mob *t;

    x = m->e->x + dx;
    y = m->e->y + dy;

    for (i=0; i < f->n_mobs; i++) {
        t = f->mobs[i];
        if (t->e->x == x && t->e->y == y && t->alive)
            return mob_attack(m, t);
    }

    if (!f->map[y][x].blocksMove)
        entity_move(m->e, dx, dy);

    return NULL;
}

struct Message* mob_take_damage(Mob *m, int amount) {
    char msg[50];

    m->hp -= amount;
    if (m->hp <= 0)
        mob_die(m);
    sprintf(msg, "%s got hit!", m->e->name);
    return message_new(msg, LIGHT2);
}

// struct Message* mob_use_item(Mob *m, Floor *f, Item *i);
