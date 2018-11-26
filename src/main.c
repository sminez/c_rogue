#include "libtcod.h"
#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include "colors.h"
#include "player.h"
#include "dungeon.h"

#define SCREEN_W 80
#define SCREEN_H 50
#define STATUS_W 80
#define STATUS_H 10
#define MAP_W 80
#define MAP_H 40

bool handle_keys();
void render_all(Dungeon* d, TCOD_console_t con);

int main() {
    bool running;
    TCOD_console_t con;
    Player* p;
    Dungeon* d;

    running = true;
    con = TCOD_console_new(SCREEN_W, SCREEN_H);
    p = init_player(0, 0);
    d = dungeon_new(MAP_W, MAP_H, p);

    TCOD_console_set_custom_font(
        "terminal16x16_gs_ro.png",
        TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_ASCII_INROW,
        16,
        16
    );

    TCOD_console_init_root(
        SCREEN_W, SCREEN_H, "Let's Loot!", false, TCOD_RENDERER_SDL
    );

    while (!TCOD_console_is_window_closed()) {
        running = handle_keys(p);
        if (!running) {
            return 0;
        }

        render_all(d, con);
    }
}

bool handle_keys(Player* p) {
    TCOD_key_t key;

    key = TCOD_console_check_for_keypress(TCOD_EVENT_KEY_PRESS);

    switch (key.vk) {
        case TCODK_NONE:
            // Nothing happened
            break;
        case TCODK_UP:
            player_move(p, -1, 0);
            break;
        case TCODK_DOWN:
            player_move(p, 1, 0);
            break;
        case TCODK_LEFT:
            player_move(p, 0, -1);
            break;
        case TCODK_RIGHT:
            player_move(p, 0, 1);
            break;
    }

    switch (key.c) {
        case 'q':
            if (key.shift) return false;
    }

    return true;
}

void render_all(Dungeon* d, TCOD_console_t con) {
    int x, y;
    Floor* f;
    Tile* t;
    Player* p;

    f = d->floors[d->depth];
    p = d->player;

    // Render the current state of the map
    TCOD_console_set_default_foreground(con, WHITE);

    for (y=0; y < f->h; y++) {
        for (x=0; x < f->w; x++) {
            t = &f->map[y][x];
            TCOD_console_set_char_foreground(con, x, y, t->fg);
            TCOD_console_set_char_background(con, x, y, t->bg, TCOD_BKGND_DEFAULT);
            TCOD_console_set_char(con, x, y, t->c);
        }
    }

    // Draw the player
    TCOD_console_put_char(
        con, p->e->x, p->e->y, p->e->c, TCOD_BKGND_DEFAULT
    );

    TCOD_console_blit(
        con, 0, 0, SCREEN_W, SCREEN_H, 0, 0, 0, 1.0, 1.0
    );
    TCOD_console_flush();
}