#include "libtcod.h"
#include "dungeon.h"
#include "player.h"
#include "colors.h"
#include "render.h"
#include "floor.h"
#include "tile.h"

void render_all(Dungeon *d, TCOD_console_t con, int w, int h, int offset) {
    Floor* f;
    Player* p;

    f = d->floors[d->current_floor];
    p = d->player;

    render_status(con, d, offset);
    render_map(con, f, p);
    // render_features(con, f):
    // render_enemies(con, f);
    render_player(con, p);

    TCOD_console_blit(con, 0, 0, w, h, 0, 0, 0, 1.0, 1.0);
    TCOD_console_flush();
}

void render_map(TCOD_console_t con, Floor *f, Player *p) {
    int x, y;
    Tile* t;

    TCOD_map_compute_fov(f->fov1, p->e->x, p->e->y, p->vision1, true, FOV_SHADOW);
    TCOD_map_compute_fov(f->fov2, p->e->x, p->e->y, p->vision2, true, FOV_SHADOW);

    for (y=0; y < f->h; y++) {
        for (x=0; x < f->w; x++) {
            t = &f->map[y][x];
            if (TCOD_map_is_in_fov(f->fov1, x, y)) {
            // if (true) {  // Uncomment for mapgen debug
                t->explored = true;
                render_tile(con, t, x, y, t->fg, t->bg);
            } else if (TCOD_map_is_in_fov(f->fov2, x, y)) {
                render_tile(con, t, x, y, DIM_FG2, BLACK);
            } else {
                if (t->explored)
                    render_tile(con, t, x, y, DIM_FG1, BLACK);
                else
                    clear_tile(con, x, y);
            }
        }
    }
}

void render_tile(TCOD_console_t con, Tile *t, int x, int y, TCOD_color_t fg, TCOD_color_t bg) {
    TCOD_console_set_char_foreground(con, x, y, fg);
    TCOD_console_set_char_background(con, x, y, bg, TCOD_BKGND_SET);
    TCOD_console_set_char(con, x, y, t->c);
}

void clear_tile(TCOD_console_t con, int x, int y) {
    TCOD_console_set_char_foreground(con, x, y, BLACK);
    TCOD_console_set_char_background(con, x, y, BLACK, TCOD_BKGND_SET);
    TCOD_console_set_char(con, x, y, ' ');
}

void render_player(TCOD_console_t con, Player *p) {
    player_color_from_health(p);
    TCOD_console_set_char_foreground(con, p->e->x, p->e->y, p->e->fg);
    TCOD_console_set_char(con, p->e->x, p->e->y, p->e->c);
}

void render_status(TCOD_console_t con, Dungeon *d, int offset) {
    Player *p;
    p = d->player;

    TCOD_console_print(
        con, 1, d->h+offset-3,
        "Lvl:%d  Hp:%d/%d  Xp:%d/%d  Gold:%d  Floor:%d",
        p->level, p->hp, p->hp_max, p->xp, p->xp_next,
        p->gold, d->current_floor+1
    );
    TCOD_console_print(
        con, 1, d->h+offset-2,
        "Str:%d  Dex:%d  Vit:%d  Int:%d",
        p->STR, p->DEX, p->VIT, p->INT
    );
}