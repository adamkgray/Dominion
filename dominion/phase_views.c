#include "phase_views.h"

void buy_phase_view(interface * p_interface, table * p_table, player * p_player) {
    int8_t opt_x = 0;
    int8_t opt_y = 0;
    int8_t m = 1;
    int16_t c;

    /* Initial render */
    draw_table(p_interface, p_table, p_player, opt_x, opt_y, "BUY");

    /* Read input */
    while (m) {
        /* Player has empty hand and must buy */
        if (p_player->hand->card_count == 0) {
            opt_x = 1;
        }

        select_treasure(p_interface, p_table, p_player, &opt_x, &opt_y, &c);

        /* Player has chosen to end buys */
        if (c == 'q') {
            p_player->buys = 0;
            /* erase status */
            move(p_interface->bottom_y - 1, 0);
            clrtoeol();
            move(p_interface->bottom_y, 0);
            clrtoeol();
            return;
        }

        /* Player wants to move coin to play area */
        if (!opt_x && p_player->hand->cards[opt_y]->type & TREASURE) {
            /* Erase where the word was */
            mvprintw((p_interface->center_y / 3) + p_player->hand->card_count, (p_interface->center_x / 2) - 8, "           ");
            /* Pop card from hand */
            card * p_card = pop_card_at(opt_y, p_player->hand);
            /* Push card into play area */
            push_card(p_card, p_player->play_area);
            /* Increment play area value */
            p_table->play_area_value += p_card->value;
            /* reset opts */
            opt_x = 0;
            opt_y = 0;
            /* re-render */
            draw_table(p_interface, p_table, p_player, opt_x, opt_y, "BUY");
        }

        /* Player wants to buy */
        if (opt_x && p_table->supply_piles[opt_y]->card_count > 0 && p_table->play_area_value >= p_table->supply_piles[opt_y]->cards[0]->cost) {
            /* Move the card from supply piles to player's dicsard */
            pop_and_push(p_player->discard, p_table->supply_piles[opt_y]);
            /* Set play area value to zero */
            p_table->play_area_value = 0;
            /* Clear the screen */
            /* break loop */
            m = 0;
        }
    }


    /* erase status */
    move(p_interface->bottom_y - 1, 0);
    clrtoeol();
    move(p_interface->bottom_y, 0);
    clrtoeol();

    /* Next buy */
    p_player->buys -= 1;
    return;
}

void select_treasure(interface * p_interface, table * p_table, player * p_player, int8_t * opt_x, int8_t * opt_y, int16_t * c) {
    while ((*c = getch()) != 10 && *c != 13) {
        switch (*c) {
            case 'q':
                /* Player ends buy phase */
                return;
            case 'd':
                /* TODO: description */
                break;
            case KEY_UP:
                if (*opt_y > 0) {
                    --(*opt_y);
                    draw_table(p_interface, p_table, p_player, *opt_x, *opt_y, "BUY");
                }
                break;
            case KEY_DOWN:
                if ((*opt_x && *opt_y < (SUPPLY_PILES - 1)) || (!(*opt_x) && *opt_y < p_player->hand->card_count - 1)) {
                    ++(*opt_y);
                    draw_table(p_interface, p_table, p_player, *opt_x, *opt_y, "BUY");
                }
                break;
            case KEY_LEFT:
                if (*opt_x == 1 && p_player->hand->card_count > 0) {
                    *opt_x = 0;
                    *opt_y = (*opt_y > p_player->hand->card_count - 1) ? p_player->hand->card_count - 1 : *opt_y;
                    draw_table(p_interface, p_table, p_player, *opt_x, *opt_y, "BUY");
                }
                break;
            case KEY_RIGHT:
                if (*opt_x == 0) {
                    *opt_x = 1;
                    draw_table(p_interface, p_table, p_player, *opt_x, *opt_y, "BUY");
                }
                break;
            default:
                break;
        }
    }
}

void action_phase_view(interface * p_interface, table * p_table, player * p_player) {
    int16_t c;          /* player input */
    int8_t m = 1;       /* variable to determine whether or not loop should continue */
    int8_t opt_y = 0;   /* index of which card is selected */

    /* Initial render */
    draw_table(p_interface, p_table, p_player, 0, 0, "ACTION");

    while (m) {
        select_action_card(p_interface, p_table, p_player, &opt_y, &c);

        /* Player ended action phase by choice */
        if (c == 'q') {
            m = 0;
            p_player->actions = 0;
            /* erase status */
            move(p_interface->bottom_y - 1, 0);
            clrtoeol();
            move(p_interface->bottom_y, 0);
            clrtoeol();
            return;
        }

        /* Player has played an action card */
        if (p_player->hand->cards[opt_y]->type & ACTION) {
            /* Clear the final card name in hand so it doesn't remain upon re-draw */
            mvprintw((p_interface->center_y / 3) + p_player->hand->card_count, (p_interface->center_x / 2) - 8, "          ");
            /* Pop the card from player's hand */
            card * p_card = pop_card_at(opt_y, p_player->hand);
            /* Push card to play area */
            push_card(p_card, p_player->play_area);
            /* Execute action card instructions */
            execute_action_card_instructions(p_interface, p_card->instructions, p_table);
            /* Break loop */
            m = 0;
        }
    }


    /* erase status */
    move(p_interface->bottom_y - 1, 0);
    clrtoeol();
    move(p_interface->bottom_y, 0);
    clrtoeol();

    /* Next action */
    p_player->actions -= 1;
    return;
}

void select_action_card(interface * p_interface, table * p_table, player * p_player, int8_t * opt_y, int16_t * c) {
    while ((*c = getch()) != 10 && *c != 13) {
        switch (*c) {
            case 'q':
                /* Player ends action phase */
                return;
            case 'd':
                /* TODO: description */
                break;
            case KEY_UP:
                if (*opt_y - 1 >= 0) {
                    --(*opt_y);
                    draw_table(p_interface, p_table, p_player, 0, *opt_y, "ACTION");
                }
                break;
            case KEY_DOWN:
                if (*opt_y < p_player->hand->card_count - 1) {
                    ++(*opt_y);
                    draw_table(p_interface, p_table, p_player, 0, *opt_y, "ACTION");
                }
                break;
            default:
                break;
        }
    }
    return;
}

void draw_table(interface * p_interface, table * p_table, player * p_player, int8_t opt_x, int8_t opt_y, char * phase) {
    int8_t x, y;
    card_stack * p_card_stack;
    card * p_card;

    /* Show status */
    mvprintw(p_interface->bottom_y - 1, 0, "Press 'q' to end current phase");
    mvprintw(p_interface->bottom_y, 0, "player: %s | phase: %s | actions: %d | buys: %d | $%d", p_player->name, phase, p_player->actions, p_player->buys, p_table->play_area_value);

    /* Show hand */
    y = (p_interface->center_y / 3);
    x = (p_interface->center_x / 2) - 8;
    mvprintw(y++, x, "HAND");
    for (int8_t i = 0; i < p_player->hand->card_count; ++i) {
        p_card = p_player->hand->cards[i];
        if (opt_x == 0 && i == opt_y) {
            attron(COLOR_PAIR(BLACK_ON_WHITE));
        }
        mvprintw(y++, x, "%-10s", p_card->name);
        attroff(COLOR_PAIR(BLACK_ON_WHITE));
    }

    /* Show play area */
    y = (p_interface->center_y / 3);
    x = (p_interface->center_x - 8);
    mvprintw(y++, x, "PLAY AREA");
    for (int8_t i = 0; i < p_player->play_area->card_count; ++i) {
        p_card = p_player->play_area->cards[i];
        mvprintw(y++, x, "%-10s", p_card->name);
    }

    /* Show supply piles */
    y = (p_interface->center_y / 3);
    x = ((p_interface->center_x / 2) + p_interface->center_x) - 8;
    mvprintw(y++, x, "SUPPLY PILES");
    for (int8_t i = 0; i < SUPPLY_PILES; ++i) {
        p_card_stack = p_table->supply_piles[i];
        if (opt_x == 1 && opt_y == i) {
            attron(COLOR_PAIR(BLACK_ON_WHITE));
        }
        mvprintw(
            y++, x,
            "[%c%c] $%d %-10s",
            (p_card_stack->card_count > 9) ? ('0' + (p_card_stack->card_count / 10)) : '0',
            (p_card_stack->card_count > 9) ? ('0' + (p_card_stack->card_count % 10)) : ('0' + p_card_stack->card_count),
            (p_card_stack->card_count > 0) ? p_card_stack->cards[0]->cost : 0,
            (p_card_stack->card_count > 0) ? p_card_stack->cards[0]->name : "-"
        );
        attroff(COLOR_PAIR(BLACK_ON_WHITE));
    }
}
