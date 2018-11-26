#ifndef _CROGUE_PLAYER_H
#define _CROGUE_PLAYER_H
#include <stdbool.h>
#include "entity.h"

#define PLAYER_HP 10

typedef struct {
    Entity* e;
    int hp;
} Player;


Player* init_player(int y, int x);
void player_move(Player* p, int dy, int dx);
void player_attack(Player* p, int dy, int dx);
void player_take_damage(Player* p, int amount);

#endif