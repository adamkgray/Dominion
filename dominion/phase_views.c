#include "phase_views.h"

void buy_phase_view(interface * p_interface, table * p_table, player * p_player) {
    int8_t opt_x = 0;
    int8_t opt_y = 0;
    int8_t m = 1;
    int16_t c;

    /* Initial render */
    render_table(p_interface, p_table, p_player, "BUY");

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
            move(p_interface->bottom_y - 1, 0); clrtoeol();
            move(p_interface->bottom_y, 0); clrtoeol();
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
            render_play_area(p_interface, p_player);
            render_hand(p_interface, p_player, opt_y);
            render_status(p_interface, p_table, p_player, "BUY");
        }

        /* Player wants to buy */
        if (opt_x && p_table->supply_piles[opt_y]->card_count > 0 && p_table->play_area_value >= p_table->supply_piles[opt_y]->cards[0]->cost) {
            /* Move the card from supply piles to player's dicsard */
            pop_and_push(p_player->discard, p_table->supply_piles[opt_y]);
            /* Set play area value to zero */
            p_table->play_area_value = 0;
            /* break loop */
            m = 0;
        }
    }


    /* erase status */
    move(p_interface->bottom_y - 1, 0); clrtoeol();
    move(p_interface->bottom_y, 0); clrtoeol();

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
                    if (opt_x) {
                        render_supply_piles(p_interface, p_table, *opt_y);
                    } else {
                        render_hand(p_interface, p_player, *opt_y);
                    }
                }
                break;
            case KEY_DOWN:
                if ((*opt_x && *opt_y < (SUPPLY_PILES - 1)) || (!(*opt_x) && *opt_y < p_player->hand->card_count - 1)) {
                    ++(*opt_y);
                    if (opt_x) {
                        render_supply_piles(p_interface, p_table, *opt_y);
                    } else {
                        render_hand(p_interface, p_player, *opt_y);
                    }
                }
                break;
            case KEY_LEFT:
                if (*opt_x == 1 && p_player->hand->card_count > 0) {
                    *opt_x = 0;
                    *opt_y = (*opt_y > p_player->hand->card_count - 1) ? p_player->hand->card_count - 1 : *opt_y;
                    render_supply_piles(p_interface, p_table, -1);
                    render_hand(p_interface, p_player, *opt_y);
                }
                break;
            case KEY_RIGHT:
                if (*opt_x == 0) {
                    *opt_x = 1;
                    render_supply_piles(p_interface, p_table, *opt_y);
                    render_hand(p_interface, p_player, -1);
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
    render_table(p_interface, p_table, p_player, "ACTION");

    while (m) {
        select_action_card(p_interface, p_table, p_player, &opt_y, &c);

        /* Player ended action phase by choice */
        if (c == 'q') {
            m = 0;
            p_player->actions = 0;
            /* erase status */
            move(p_interface->bottom_y - 1, 0); clrtoeol();
            move(p_interface->bottom_y, 0); clrtoeol();
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
    move(p_interface->bottom_y - 1, 0); clrtoeol();
    move(p_interface->bottom_y, 0); clrtoeol();

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
                    render_hand(p_interface, p_player, *opt_y);
                }
                break;
            case KEY_DOWN:
                if (*opt_y < p_player->hand->card_count - 1) {
                    ++(*opt_y);
                    render_hand(p_interface, p_player, *opt_y);
                }
                break;
            default:
                break;
        }
    }
    return;
}
