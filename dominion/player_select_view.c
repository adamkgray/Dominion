#include "player_select_view.h"

void player_select_view(interface * p_interface, int8_t * player_count, int8_t * player_types, char * names) {
    /* Get player count */
    select_player_count(p_interface, player_count, 2);

    /* Initialize all spaces in names to null */
    for (int8_t i = 0; i < (*player_count * 8); ++i) {
        names[i] = '\0';
    }

    /* Get human/cpu int */
    human_or_cpu(p_interface, *player_count, player_types, 0);

    /* Get names if any human players */
    if (*player_types & 7) {
        enter_names(p_interface, *player_count, *player_types, names, 0, 0);
    }

    clear();
    return;
}

void enter_names(interface * p_interface, int8_t player_count, int8_t player_types, char * names, int8_t option, int8_t pos) {
    int16_t y = (p_interface->center_y / 2) - 1;
    int16_t x = p_interface->center_x - 17;

    if (option < player_count) {
        if (player_types & (int8_t)pow(2, option)) { /* Player is flagged as human */
            /* Print current name input */
            mvprintw(y++, x, "Enter name for player [%d]: %.8s", option + 1, names + (8 * option));
            mvprintw(y--, x, "(8 characters max)");

            int16_t c = getch();
            if (pos < 8 && isalpha(c)) {                        /* If input is alphabetical ... */
                (names + (8 * option))[pos++] = c;              /* update the names array at correct pos */
            } else if (pos > 0 && (c == '\b' || c == 127)) {    /* If pos greater than 0 and input is backspace ...*/
                mvprintw(y, x + 26 + pos, " ");                 /* clear the previous character */
                (names + (8 * option))[--pos] = '\0';           /* Set the previous character in the names array to null */
            } else if (c == 10 || c == 13) {                    /* If input is 'enter' ... */
                clear();                                        /* Clear the screen and move to next option */
                return enter_names(p_interface, player_count, player_types, names, option + 1, 0);
            }
            /* Otherwise, it's bad input, return the view as it is */
            return enter_names(p_interface, player_count, player_types, names, option, pos);
        } else {
            /* Player is not flagged as human, move onto the next option */
            return enter_names(p_interface, player_count, player_types, names, option + 1, pos);
        }
    }

    clear();
    return;
}

void select_player_count(interface * p_interface, int8_t * player_count, int8_t option) {
    int16_t y = (p_interface->center_y / 2) - 1;
    int16_t x = p_interface->center_x - 12;

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

    int16_t c = getch();
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

void human_or_cpu(interface * p_interface, int8_t player_count, int8_t * player_types, int8_t option) {
    int16_t y = (p_interface->center_y / 2) - 1;
    int16_t x = p_interface->center_x - 8;

    for (int8_t i = 0; i < player_count; ++i) {
        if (i == option) { attron(COLOR_PAIR(BLACK_ON_WHITE)); }
        mvprintw(y++, x, "player [%d] %s", i + 1, ((int8_t)pow(2, i) & *player_types) ? "human" : "cpu  ");
        if (i == option) { attroff(COLOR_PAIR(BLACK_ON_WHITE)); }
    }

    int16_t c = getch();
    switch(c) {
        case KEY_UP:
            option -= (option > 0) ? 1 : 0;
            return human_or_cpu(p_interface, player_count, player_types, option);
        case KEY_DOWN:
            option += (option < player_count - 1) ? 1 : 0;
            return human_or_cpu(p_interface, player_count, player_types, option);
        case KEY_LEFT:
            *player_types |= (int8_t)pow(2, option);
            return human_or_cpu(p_interface, player_count, player_types, option);
        case KEY_RIGHT:
            *player_types &= ~(int8_t)pow(2, option);
            return human_or_cpu(p_interface, player_count, player_types, option);
        case 10:
        case 13:
            clear();
            return;
        default:
            return human_or_cpu(p_interface, player_count, player_types, option);
    }
}

