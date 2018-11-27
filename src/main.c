#include "libtcod.h"
#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include "dungeon.h"
#include "colors.h"
#include "player.h"
#include "floor.h"

#define WIDTH 80
#define SCREEN_H 50
#define STATUS_H 5
#define MAP_H SCREEN_H - STATUS_H

bool handle_keys(Player *p, Floor *f);
void render_all(Dungeon *d, TCOD_console_t con);

int main() {
    bool running;
    TCOD_console_t con;
    Player *p;
    Dungeon *d;
    Floor *f;

    running = true;
    con = TCOD_console_new(WIDTH, SCREEN_H);
    p = init_player(0, 0);
    d = dungeon_new(WIDTH, MAP_H, p);
    f = d->floors[0];

    TCOD_console_set_custom_font(
        "terminal16x16_gs_ro.png",
        TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_ASCII_INROW,
        16,
        16
    );

    TCOD_console_init_root(
        WIDTH, SCREEN_H, "Let's Loot!", false, TCOD_RENDERER_SDL
    );

    render_all(d, con);
    while (!TCOD_console_is_window_closed()) {
        running = handle_keys(p, f);
        if (!running) {
            return 0;
        }

        render_all(d, con);
    }
}

bool handle_keys(Player *p, Floor *f) {
    TCOD_key_t key;

    key = TCOD_console_wait_for_keypress(true);

    switch (key.vk) {
        case TCODK_NONE:
            // Nothing happened
            break;
        case TCODK_UP:
            player_move(p, f, -1, 0);
            break;
        case TCODK_DOWN:
            player_move(p, f, 1, 0);
            break;
        case TCODK_LEFT:
            player_move(p, f, 0, -1);
            break;
        case TCODK_RIGHT:
            player_move(p, f, 0, 1);
            break;
        default:
            break;
    }

    switch (key.c) {
        case 'q':
            if (key.shift)
				return false;
			break;
        case 'k':
            player_move(p, f, -1, 0);
            break;
        case 'j':
            player_move(p, f, 1, 0);
            break;
        case 'h':
            player_move(p, f, 0, -1);
            break;
        case 'l':
            player_move(p, f, 0, 1);
            break;
    }

    return true;
}

void render_all(Dungeon *d, TCOD_console_t con) {
    int x, y;
    Floor* f;
    Tile* t;
    Player* p;

    f = d->floors[d->currentFloor];
    p = d->player;

    TCOD_console_set_default_foreground(con, LIGHT0);
    TCOD_console_set_default_background(con, DARK0);

    // Base map tiles
    for (y=0; y < f->h; y++) {
        for (x=0; x < f->w; x++) {
            t = &f->map[y][x];
            TCOD_console_set_char_foreground(con, x, y, t->fg);
            TCOD_console_set_char_background(con, x, y, t->bg, TCOD_BKGND_SET);
            TCOD_console_set_char(con, x, y, t->c);
        }
    }

    // Features, items, traps...

    // Enemies

    // Player (TODO: set color based on current health perc)
    TCOD_console_set_char_foreground(con, p->e->x, p->e->y, LIGHT0);
    TCOD_console_set_char(con, p->e->x, p->e->y, p->e->c);

    TCOD_console_blit(
        con, 0, 0, WIDTH, SCREEN_H, 0, 0, 0, 1.0, 1.0
    );
    TCOD_console_flush();
}
