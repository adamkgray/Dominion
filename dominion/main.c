/* Dominion */
#include "headers.h"

int main(void) {
    /* Gather plyer details */
    int player_count = 2;
    char * names[player_count];
    names[0] = "human";
    names[1] = "cpu";

    /* Create a new table */
    struct table * p_table = new_table(select_playing_cards(base_set()), player_count, names);
    if (p_table == NULL) { fprintf(stderr, "Memory error"); return 1; }

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

    /* Initialize interface */
    struct interface * p_interface = (struct interface *)malloc(sizeof(struct interface));
    p_interface->left_x   = 0;
    p_interface->right_x  = COLS - 1;
    p_interface->top_y    = 0;
    p_interface->bottom_y = LINES - 1;
    p_interface->center_x = (COLS - 1) / 2;
    p_interface->center_y = (LINES - 1) / 2;

    title_screen(p_interface);

    int i, j;
    /* Shuffle decks */
    for (i = 0; i < p_table->player_count; ++i) {
        randomize_cards(p_table->players[i]->deck->cards, 10);
    }
    /* Draw five cards */
    for (i = 0; i < p_table->player_count; ++i) {
        for (j = 0; j < 5; ++j) {
            draw(p_table->players[i]);
        }
    }

    /* Begin the game */
    gameplay(p_table);

    /* Stop curses */
    endwin();
    return 0;
}
