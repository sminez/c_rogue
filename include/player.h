#ifndef _CROGUE_PLAYER_H
#define _CROGUE_PLAYER_H
#include <stdbool.h>
#include "entity.h"
#include "floor.h"

#define PLAYER_BASE_HP 10
#define PLAYER_BASE_VISION 5

typedef struct {
    Entity* e;
    int hp;
    int vision;
} Player;


Player* init_player(int y, int x);
void player_move(Player* p, Floor* f, int dy, int dx);
void player_attack(Player* p, int dy, int dx);
void player_take_damage(Player* p, int amount);

#endif