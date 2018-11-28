#include "libtcod.h"
#include <stdbool.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include "dungeon.h"
#include "render.h"
#include "colors.h"
#include "player.h"
#include "floor.h"

#define WIDTH 100
#define SCREEN_H 60
#define STATUS_H 5
#define MAP_H SCREEN_H - STATUS_H

bool handle_keys(Player *p, Dungeon *d);

int main() {
    bool running;
    TCOD_console_t con;
    Player *p;
    Dungeon *d;

    running = true;
    con = TCOD_console_new(WIDTH, SCREEN_H);
    p = init_player(0, 0);
    d = dungeon_new(WIDTH, MAP_H, p);

    TCOD_console_set_custom_font(
        // "terminal16x16_gs_ro.png",
        // TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_ASCII_INROW,
        "Kelora_16x16_diagonal-clouds.png",
        TCOD_FONT_LAYOUT_ASCII_INROW,
        16, 16
    );
    TCOD_console_init_root(WIDTH, SCREEN_H, "Let's Loot!", false, TCOD_RENDERER_SDL);
    TCOD_console_set_default_foreground(con, LIGHT0);
    TCOD_console_set_default_background(con, BLACK);

    while (!TCOD_console_is_window_closed()) {
        render_all(d, con, WIDTH, SCREEN_H, STATUS_H);
        running = handle_keys(p, d);
        if (!running) {
            return 0;
        }
    }
}

bool handle_keys(Player *p, Dungeon *d) {
    TCOD_key_t key;
    Floor *f;
    key = TCOD_console_wait_for_keypress(true);
    f = d->floors[d->current_floor];

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
        case TCODK_ENTER:
            if (key.lalt)
                TCOD_console_set_fullscreen(!TCOD_console_is_fullscreen());
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
        case ',':  // <
            if (key.shift && f->map[p->e->y][p->e->x].tt == stairs_up)
                if (d->current_floor != 0)
                    dungeon_move_to_floor(
                        d, d->current_floor-1, d->current_floor
                    );
            break;
        case '.':  // >
            if (key.shift && f->map[p->e->y][p->e->x].tt == stairs_down)
                if (d->current_floor != N_FLOORS-1)
                    dungeon_move_to_floor(
                        d, d->current_floor+1, d->current_floor
                    );
            break;
        default:
            break;
    }
    return true;
}