#ifndef _CROGUE_DUNGEON_H
#define _CROGUE_DUNGEON_H
#include "player.h"
#include "floor.h"

#define N_FLOORS 10

typedef struct {
    int w;
    int h;
    int depth;
    Player* player;
    Floor* floors[N_FLOORS];
} Dungeon;

Dungeon* dungeon_new(int w, int h, Player* p);
void dungeon_new_floor(Dungeon* d, int ix);

#endif