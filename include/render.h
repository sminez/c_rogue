#ifndef _CROGUE_RENDER_H
#define _CROGUE_RENDER_H

#include "libtcod.h"
#include "dungeon.h"
#include "player.h"
#include "floor.h"
#include "tile.h"

typedef struct {
    char *m;
    TCOD_color_t c;
} Message;

Message* message_new(char *m, TCOD_color_t c);
void render_all(Dungeon *d, TCOD_console_t con, int w, int h, int offset);
void render_tile(TCOD_console_t con, Tile *t, int x, int y, TCOD_color_t fg, TCOD_color_t bg);
void clear_tile(TCOD_console_t con, int x, int y);
void render_map(TCOD_console_t con, Floor *f, Player *p);
void render_player(TCOD_console_t con, Player *p);
void render_status(TCOD_console_t con, Dungeon *d, int offset);

#endif