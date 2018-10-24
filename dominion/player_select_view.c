#include "player_select_view.h"

void player_select_view(interface * p_interface, int8_t * player_count, char * names) {
    /* Get player count */
    select_player_count(p_interface, player_count);

    /* Initialize all spaces in names to null */
    for (int8_t i = 0; i < (*player_count * 8); ++i) {
        names[i] = '\0';
    }

    /* Auto name each player 'a', 'b' and 'c' for now */
    names[0]  = 'a';
    names[8]  = 'b';
    names[16] = 'c';

    clear();
    return;
}

void select_player_count(interface * p_interface, int8_t * player_count) {
    int16_t c, i;
    i = 0;

    mvprintw(
        (p_interface->center_y / 2) - 1,    /* y */
        p_interface->center_x - 12,         /* x */
        "Select number of players"          /* text */
    );

    /* Selection defaults to two */
    draw_selection(p_interface, i);

    while ((c = getch()) != 10 && c != 13) {
        switch (c) {
            case KEY_UP:
                /* Two is selected */
                if (i) {
                    i = 0;
                    draw_selection(p_interface, i);
                }
                break;
            case KEY_DOWN:
                /* Three is selected */
                if (!i) {
                    i = 1;
                    draw_selection(p_interface, i);
                }
                break;
            default:
                break;
        }
    }

    *player_count = (i) ? 3 : 2;
    return;
}

void draw_selection(interface * p_interface, int8_t opt) {
    switch (opt) {
        case 0:
            attron(COLOR_PAIR(BLACK_ON_WHITE));
            mvprintw(
                (p_interface->center_y / 2),        /* y */
                p_interface->center_x - 3,          /* x */
                " two "                             /* text */
            );
            attroff(COLOR_PAIR(BLACK_ON_WHITE));
            mvprintw(
                (p_interface->center_y / 2) + 1,    /* y */
                p_interface->center_x - 3,          /* x */
                "three"                             /* text */
            );
            break;
        case 1:
            mvprintw(
                (p_interface->center_y / 2),        /* y */
                p_interface->center_x - 3,          /* x */
                " two "                             /* text */
            );
            attron(COLOR_PAIR(BLACK_ON_WHITE));
            mvprintw(
                (p_interface->center_y / 2) + 1,    /* y */
                p_interface->center_x - 3,          /* x */
                "three"                             /* text */
            );
            attroff(COLOR_PAIR(BLACK_ON_WHITE));
            break;
    }
}
