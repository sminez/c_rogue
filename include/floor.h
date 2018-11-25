#include <stdbool.h>

#ifndef _CROGUE_FLOOR_H
#define _CROGUE_FLOOR_H

#define MAX_ROOM_TRIES 1000
#define MIN_ROOM_SIZE 7
#define MAX_ROOM_SIZE 14

typedef struct {
    int w;
    int h;
    int depth;
} Floor;

#endif