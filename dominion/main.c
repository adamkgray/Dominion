/* Dominion */
#include "ncurses.h"
#include "definitions.h"
#include "dominion_base.h"
#include "interface.h"
#include "render.h"
#include "player_select_view.h"
#include "table.h"
#include "randomize.h"
#include "draw.h"
#include "gameplay.h"

int main(void) {
    /* Initialize curses */
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    clear();

    /* Color combinations */
    init_pair(BLUE_ON_WHITE, COLOR_BLUE, COLOR_WHITE);
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);

    /* Initialize interface */
    interface * p_interface = (interface *)malloc(sizeof(interface));
    if (p_interface == NULL) {
        endwin();
        fprintf(stderr, "Memory error\n");
        return 1;
    }

    p_interface->left_x   = 0;
    p_interface->right_x  = COLS - 1;
    p_interface->top_y    = 0;
    p_interface->bottom_y = LINES - 1;
    p_interface->center_x = (COLS - 1) / 2;
    p_interface->center_y = (LINES - 1) / 2;

    /* Show title view */
    render_title(p_interface);

    int8_t player_count;
    char * names = (char *)malloc(24 * sizeof(char));
    if (names == NULL) {
        endwin();
        fprintf(stderr, "Memory error\n");
        return 1;
    }

    /* Show player select view */
    player_select_view(p_interface, &player_count, names);

    /* Create a new table */
    table * p_table = new_table(select_playing_cards(base_set()), player_count, names);
    if (p_table == NULL) {
        endwin();
        fprintf(stderr, "Memory error\n");
        return 1;
    }

    /* Shuffle decks */
    for (int8_t i = 0; i < p_table->player_count; ++i) {
        randomize_cards(p_table->players[i]->deck->cards, 10);
    }

    /* Draw five cards */
    for (int8_t i = 0; i < p_table->player_count; ++i) {
        for (int8_t j = 0; j < 5; ++j) {
            draw(p_table->players[i]);
        }
    }

    /* Begin the game */
    gameplay(p_interface, p_table);

    /* Render game over & overview */

    /* Stop curses */
    endwin();
    return 0;
}
