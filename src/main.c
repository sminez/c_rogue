#include "libtcod.h"
#include <malloc.h>
#include <stdio.h>

#define W 80
#define H 50

int main() {
    TCOD_key_t *key;
    TCOD_mouse_t *mouse;

    key = malloc(sizeof(TCOD_key_t));
    mouse = malloc(sizeof(TCOD_mouse_t));

    TCOD_console_set_custom_font(
        "terminal16x16_gs_ro.png",
        TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_ASCII_INROW,
        16,
        16
    );
    TCOD_console_init_root(
        W, H, "cRogue", false, TCOD_RENDERER_SDL
    );
    TCOD_console_t con = TCOD_console_new(W, H);

    while (!TCOD_console_is_window_closed()) {
        TCOD_sys_check_for_event(TCOD_EVENT_KEY_PRESS, key, mouse);
        TCOD_console_flush();
    }

    free(key);
    free(mouse);
}