#include <stdbool.h>

#ifndef _CROGUE_ROOM_H
#define _CROGUE_ROOM_H

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
    int id;
} Room;

Room* new_room(int x, int y, int w, int h);
int* room_center(Room* r);
int* room_random_point(Room* r, int offset);
bool room_overlaps_with(Room* r, Room* s);
bool room_h_with(Room* r, Room* s);

#endif