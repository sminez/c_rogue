#ifndef _CROGUE_MOB_H
#define _CROGUE_MOB_H
#include <stdbool.h>
#include "libtcod/src/libtcod/color.h"
#include "entity.h"
#include "floor.h"

typedef enum {
    head, neck, body,
    lhand, rhand, ring1, ring2,
    legs, feet
} Slot;

typedef enum {
    Str, Dex, Vit, Int
} Skill;

// Anything that is 'Alive' (including the player) has a Mob instance
typedef struct {
    Entity *e,;
    // Stats
    int STR, DEX, VIT, INT;
    int hp, hp_max;
    int aggro_range;
    // TODO: Add hearing and vision?
    // AI *ai;
    // States
    bool alive, asleep, stunned, confused, frightened;
    // Equipment (TODO)
    // Item *head, *neck, *body, *lhand, *rhand;
    // Item *ring1, *ring2, *legs, *feet;
} Mob;

Mob* mob_new(
    char c, char *name, TCOD_color_t fg,
    int STR, int DEX, int VIT, int INT, int hp,
    int vision, int hearing
);

// Helpers
// void mob_equip(Mob *m, Floor *f, Item *i, Slot s);
int mob_get_ac(Mob *m);
int mob_get_ev(Mob *m);
int mob_skill_check(Mob *m, Skill s, int modifier);

// Actions (Should all return Messages*)
void mob_act(Mob*m, Floor *f);
void mob_attack(Mob *m, Mob *target);
void mob_die(Mob *m);
void mob_heal(Mob *m, int amount);
void mob_move_or_attack(Mob *m, Floor *f, int dy, int dx);
void mob_take_damage(Mob *m, int amount);
// void mob_use_item(Mob *m, Floor *f, Item *i);

// Enemy constructors
Mob* mob_new_bat(int level);       // grey b
Mob* mob_new_dweller(int level);   // blue d
Mob* mob_new_goblin(int level);    // green g
Mob* mob_new_mouse(int level);     // white m
Mob* mob_new_orc(int level);       // d_green o
Mob* mob_new_pig(int level);       // pink p
Mob* mob_new_sentinal(int level);  // red S

#endif