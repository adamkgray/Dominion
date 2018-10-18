#include "player_select_view.h"

int player_select_view(struct interface * p_interface, int * player_count, int * player_types, char * names) {
    clear();
    select_player_count(p_interface, player_count, 2);             /* Get player count */
    names = (char *)malloc((*player_count * 8) * sizeof(char));    /* Player names are 8 characters max */
    if (names == NULL) { return 0; }                               /* Return if fail */
    human_or_cpu(p_interface, *player_count, player_types, 0);     /* Get human/cpu int */
    if (*player_types & 7) { enter_names(p_interface, *player_count, *player_types, names); } /* If there are human players, get names */
    return 1;   /* Return success */
}

void enter_names(struct interface * p_interface, int player_count, int player_types, char * names) {
    return;
}

void select_player_count(struct interface * p_interface, int * player_count, int option) {
    clear();    /* Clear screen */

    int y = (p_interface->center_y / 2) - 1;
    int x = p_interface->center_x - 12;

    mvprintw(y++, x, "Select number of players");
    ++y;
    if (option == 2) {
        x += 8;
        attron(COLOR_PAIR(BLACK_ON_WHITE));
        mvprintw(y++, x, " two ");
        attroff(COLOR_PAIR(BLACK_ON_WHITE));
        mvprintw(y, x, "three");
    } else {
        x += 8;
        mvprintw(y++, x, " two ");
        attron(COLOR_PAIR(BLACK_ON_WHITE));
        mvprintw(y, x, "three");
        attroff(COLOR_PAIR(BLACK_ON_WHITE));
    }

    int c = getch();
    switch (c) {
        case KEY_UP:
            return select_player_count(p_interface, player_count, 2);
       case KEY_DOWN:
            return select_player_count(p_interface, player_count, 3);
       case 10: /* line feed */
       case 13: /* carriage return */
            *player_count = option;
            return;
       default:
            return select_player_count(p_interface, player_count, option);
    }
}

void human_or_cpu(struct interface * p_interface, int player_count, int * player_types, int option) {
    clear();

    int y = (p_interface->center_y / 2) - 1;
    int x = p_interface->center_x - 8;

    for (int i = 0; i < player_count; ++i) {
        if (i == option) { attron(COLOR_PAIR(BLACK_ON_WHITE)); }
        mvprintw(y++, x, "player [%d] %s", i + 1, ((int)pow(2, i) & *player_types) ? "human" : "cpu  ");
        if (i == option) { attroff(COLOR_PAIR(BLACK_ON_WHITE)); }
    }

    int c = getch();
    switch(c) {
        case KEY_UP:
            option -= (option > 0) ? 1 : 0;
            return human_or_cpu(p_interface, player_count, player_types, option);
        case KEY_DOWN:
            option += (option < player_count - 1) ? 1 : 0;
            return human_or_cpu(p_interface, player_count, player_types, option);
        case KEY_LEFT:
            *player_types |= (int)pow(2, option);
            return human_or_cpu(p_interface, player_count, player_types, option);
        case KEY_RIGHT:
            *player_types &= ~(int)pow(2, option);
            return human_or_cpu(p_interface, player_count, player_types, option);
        case 10:
        case 13:
            return;
        default:
            return human_or_cpu(p_interface, player_count, player_types, option);
    }

    /*
     * 1 = human, 0 = computer
     *
     * n = int
     *
     * 2 players:
     * 00 01 10 11
     * 0  1  2  3
     *
     * p1 = n & 1
     * p2 = n & 2
     *
     * 3 players:
     * 000 001 010 011 100 101 110 111
     * 0   1   2   3   4   5   6   7
     *
     * p1 = n & 1
     * p2 = n & 2
     * p3 = n & 4
     *
     * for (i = 0; i < player_count; ++i) {
     *     p_table->players[i]->type = n & pow(2, i);
     * }
     */
}

