#include "execute_instructions.h"

void execute_action_card_instructions(interface * p_interface, int32_t instructions, table * p_table) {
    /* Each instruction is an integer that can be represented by 5 bits (max 6 instructions per card, i.e. 30 bits )
     * To get the next instruction, we 'AND' the instruction integer with 31 (11111)
     * If it's 0 stop, otherwise execute it
     */
    if (instructions & 31) {
        execute_instruction(p_interface, (int8_t)(instructions & 31), p_table);
        /* Bitshift 5 to the right to get the next instruction */
        return execute_action_card_instructions(p_interface, instructions >> 5, p_table);
    }
    return;
}

void execute_instruction(interface * p_interface, int8_t instruction, table * p_table) {
    /* Execute a discrete instruction from an action card.
     * Instructions may perform logic and/or bring up a new view to get player input
     */
    player * p_player = p_table->players[p_table->turn];
    switch (instruction) {
        case PLUS_CARD:
            draw(p_player);
            break;
        case PLUS_ACTION:
            ++(p_player->actions);
            break;
        case PLUS_BUY:
            ++(p_player->buys);
            break;
        case PLUS_COIN:
            p_table->play_area_value += 1;
            break;
        case EACH_OTHER_PLAYER_GAINS_CURSE:
            each_other_player_gains_curse(p_table);
            break;
        case EACH_OTHER_PLAYER_DRAWS_CARD:
            each_other_player_draws_card(p_table);
        case GAIN_SILVER_TO_DECK:
            gain_silver_to_deck(p_player, p_table);
            break;
        case GAIN_GOLD:
            gain_gold(p_player, p_table);
        case TRASH_UP_TO_FOUR_CARDS:
            clear(); /* Clear the screen for new view */
            trash_up_to_four_cards(p_interface, p_player);
            break;
        case GAIN_CARD_COSTING_UP_TO_FOUR:
            clear(); /* Clear screen for new view */
            gain_card_costing_up_to_four(p_interface, p_table, p_player);
            break;
        case TRASH_COPPER_FOR_PLUS_THREE:
            clear();
            trash_copper_for_plus_three(p_interface, p_table, p_player);
            break;
        default:
            break;
    }
    return;
}


/* Reads from stdin to select a card from the hand. Re-renders just the hand */
void select_from_hand(interface * p_interface, player * p_player, int8_t * opt_y, int16_t * c) {
    while ((*c = getch()) != 10 && *c != 13) {
        switch (*c) {
            case KEY_DOWN:
                if (*opt_y < p_player->hand->card_count - 1) {
                    ++(*opt_y);
                    render_hand(p_interface, p_player, *opt_y);
                }
            case KEY_UP:
                if (*opt_y > 0) {
                    --(*opt_y);
                    render_hand(p_interface, p_player, *opt_y);
                }
            case 'q':
                return;
            default:
                break;
        }
    }
    return;
}

/* Reads from stdin to select a card from the supply piles. Re-renders just the supply piles */
void select_from_supply_piles(interface * p_interface, table * p_table, int8_t * opt_y, int16_t * c) {
    while ((*c = getch()) != 10 && *c != 13) {
        switch (*c) {
            case KEY_DOWN:
                if (*opt_y < SUPPLY_PILES - 1) {
                    ++(*opt_y);
                    render_supply_piles(p_interface, p_table, *opt_y);
                }
                break;
            case KEY_UP:
                if (*opt_y > 0) {
                    --(*opt_y);
                    render_supply_piles(p_interface, p_table, *opt_y);
                }
                break;
            case 'q':
                return;
            default:
                break;
        }
    }
    return;
}

void trash_copper_for_plus_three(interface * p_interface, table * p_table, player * p_player) {
    int8_t opt_y = 0;
    int16_t c;
    int8_t m = 1;

    /* Show status */
    move(p_interface->bottom_y - 1, 0); clrtoeol();
    move(p_interface->bottom_y , 0); clrtoeol();
    mvprintw(p_interface->bottom_y, 0, "Trash a copper or press 'q' to end");

    render_hand(p_interface, p_player, opt_y);

    while (m) {
        select_from_hand(p_interface, p_player, &opt_y, &c);

        if (c == 'q') {
            return;
        }

        if (p_player->hand->cards[opt_y]->type & TREASURE && p_player->hand->cards[opt_y]->value == 1) {
            /* Pop card from hand */
            card * p_card = pop_card_at(opt_y, p_player->hand);

            /* Add 3 to play area value */
            p_table->play_area_value += 3;

            /* Trashing cards frees up memory too */
            p_card = NULL;
            free(p_card);

            m = 0;
        }
    }
    return;
}

void gain_card_costing_up_to_four(interface * p_interface, table * p_table, player * p_player) {
    int8_t opt_y = 0;
    int16_t c;

    /* Show status */
    move(p_interface->bottom_y - 1, 0); clrtoeol();
    move(p_interface->bottom_y , 0); clrtoeol();
    mvprintw(p_interface->bottom_y, 0, "Gain a card costing up to $4");

    render_hand(p_interface, p_player, -1);
    render_supply_piles(p_interface, p_table, opt_y);

    while (1) {
        select_from_supply_piles(p_interface, p_table, &opt_y, &c);

        if (c == 'q') {
            return;
        }

        if (p_table->supply_piles[opt_y]->card_count > 0 && p_table->supply_piles[opt_y]->cards[0]->cost <= 4) {
            pop_and_push(p_player->discard, p_table->supply_piles[opt_y]);
            clear();
            return;
        }
    }
    return;
}

void trash_up_to_four_cards(interface * p_interface, player * p_player) {
    int8_t m = 4;
    int16_t c;
    int8_t opt_y = 0;

    /* Show status */
    move(p_interface->bottom_y - 1, 0); clrtoeol();
    move(p_interface->bottom_y , 0); clrtoeol();
    mvprintw(p_interface->bottom_y - 1, 0, "Press 'q' to end trashes");

    render_hand(p_interface, p_player, opt_y);

    while (m) {
        mvprintw(p_interface->bottom_y , 0, "Trashes remaining: %d", m);

        select_from_hand(p_interface, p_player, &opt_y, &c);

        if (c == 'q') {
            return;
        }

        /* Erase where the word was */
        mvprintw((p_interface->center_y / 3) + p_player->hand->card_count, (p_interface->center_x / 2) - 8, "          ");

        /* Pop card from hand */
        card * p_card = pop_card_at(opt_y, p_player->hand);

        /* Trashing cards frees up memory too */
        p_card = NULL;
        free(p_card);

        /* Decrement trashes */
        --m;
    }
    return;
}

void each_other_player_draws_card(table * p_table) {
    for (int8_t i = 0; i < p_table->player_count; ++i) {
        if (i != p_table->turn) {
            draw(p_table->players[i]);
        }
    }
}

void gain_gold(player * p_player, table * p_table) {
    pop_and_push(p_player->discard, p_table->supply_piles[GOLD]);
    card ** golds = (card **)realloc(p_table->supply_piles[GOLD]->cards, p_table->supply_piles[GOLD]->card_count * sizeof(card *));
    if (golds != NULL) {
        p_table->supply_piles[GOLD]->cards = golds;
    }
}

void gain_silver_to_deck(player * p_player, table * p_table) {
    pop_and_push(p_player->deck, p_table->supply_piles[SILVER]);
    card ** silvers = (card **)realloc(p_table->supply_piles[SILVER]->cards, p_table->supply_piles[SILVER]->card_count * sizeof(card *));
    if (silvers != NULL) {
        p_table->supply_piles[SILVER]->cards = silvers;
    }
}

void each_other_player_gains_curse(table * p_table) {
    for (int8_t i = 0; i < p_table->player_count; ++i) {
        if (i != p_table->turn) {
            pop_and_push(p_table->players[i]->discard, p_table->supply_piles[0]);
        }
    }
}
