#include <stdbool.h>

#ifndef _CROGUE_ROOM_H
#define _CROGUE_ROOM_H

#define ROOM_PADDING 1

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
    int id;
} Room;

Room* room_new(int x, int y, int w, int h, int id);
void room_center(Room* r, int* x, int* y);
void room_random_point(Room* r, int offset, int* x, int* y);
bool room_overlaps_with(Room* r, Room* s);
bool room_h_with(Room* r, Room* s);

#endif