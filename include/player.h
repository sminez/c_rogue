#ifndef _CROGUE_PLAYER_H
#define _CROGUE_PLAYER_H
#include <stdbool.h>
#include "entity.h"
#include "floor.h"

#define PLAYER_BASE_HP 10
#define PLAYER_BASE_VISION1 8
#define PLAYER_BASE_VISION2 15
#define PLAYER_XP_MUL 1.2
#define PLAYER_BASE_STR 3
#define PLAYER_BASE_DEX 3
#define PLAYER_BASE_VIT 3
#define PLAYER_BASE_INT 3

typedef struct {
    Entity *e;
    int STR;
    int DEX;
    int VIT;
    int INT;
    int hp;
    int hp_max;
    int xp;
    int xp_next;
    int level;
    int gold;
    int vision1;
    int vision2;
} Player;


Player* init_player(int y, int x);
void player_move(Player *p, Floor *f, int dy, int dx);
void player_attack(Player *p, int dy, int dx);
void player_take_damage(Player *p, int amount);
void player_color_from_health(Player *p);
void player_level_up(Player *p);

#endif