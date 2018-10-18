#include "player_select_view.h"

int player_select_view(struct interface * p_interface, int * player_count, int * player_types, char * names) {
    select_player_count(p_interface, player_count, 2);             /* Get player count */
    names = (char *)malloc((*player_count * 8) * sizeof(char));    /* Player names are 8 characters max */
    if (names == NULL) { return 0; }                               /* Return if fail */
    for (int i = 0; i < (*player_count * 8); ++i) { names[i] = '\0'; } /* Initialize all spaces in names to null */
    human_or_cpu(p_interface, *player_count, player_types, 0);     /* Get human/cpu int */
    if (*player_types & 7) {                                       /* Get names if any */
        enter_names(p_interface, *player_count, *player_types, names, 0, 0);
    }
    clear();
    return 1;   /* Return success */
}

void enter_names(struct interface * p_interface, int player_count, int player_types, char * names, int option, int pos) {
    /* TODO: fix */
    int y = (p_interface->center_y / 2) - 1;
    int x = p_interface->center_x - 17;

    if (option < player_count) {
        if (player_types & (int)pow(2, option)) {
            names += (8 * option);
            mvprintw(y, x, "Enter name for player [%d]: %.8s", option + 1, names);

            int c = getch();
            if (pos < 8 && isalpha(c)) {
                names[pos++] = c;
            } else if (pos > 0 && c == '\b') {
                names[--pos] = '\0';
            } else if (c == 10 || c == 13) {
                clear();
                return enter_names(p_interface, player_count, player_types, names, option + 1, 0);
            }

            return enter_names(p_interface, player_count, player_types, names, option, pos);
        }
    }

    clear();
    return;
}

void select_player_count(struct interface * p_interface, int * player_count, int option) {
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
            clear();
            return;
       default:
            return select_player_count(p_interface, player_count, option);
    }
}

void human_or_cpu(struct interface * p_interface, int player_count, int * player_types, int option) {
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
            clear();
            return;
        default:
            return human_or_cpu(p_interface, player_count, player_types, option);
    }
}

