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
            trash_up_to_four_cards(p_interface, p_player, 0, 4);
            break;
        case GAIN_CARD_COSTING_UP_TO_FOUR:
            clear(); /* Clear screen for new view */
            gain_card_costing_up_to_four(p_interface, p_table, p_player, 0);
            break;
        default:
            break;
    }
    return;
}

void gain_card_costing_up_to_four(interface * p_interface, table * p_table, player * p_player, int8_t opt_y) {
    /* Show status */
    mvprintw(p_interface->bottom_y, 0, "Gain a card costing up to $4");

    /* Show supply piles */
    int8_t y = (p_interface->center_y / 3);
    int8_t x = ((p_interface->center_x / 2) + p_interface->center_x) - 8;
    mvprintw(y++, x, "SUPPLY PILES");
    for (int8_t i = 0; i < SUPPLY_PILES; ++i) {
        card_stack * p_card_stack = p_table->supply_piles[i];
        if (opt_y == i) {
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

    int16_t c = getch();
    switch (c) {
        case 10:
        case 13:
            if (p_table->supply_piles[opt_y]->card_count > 0 && p_table->supply_piles[opt_y]->cards[0]->cost <= 4) {
                pop_and_push(p_player->discard, p_table->supply_piles[opt_y]);
                clear();
                return;
            }
            break;
        case KEY_DOWN:
            if (opt_y < SUPPLY_PILES - 1) {
                return gain_card_costing_up_to_four(p_interface, p_table, p_player, opt_y + 1);
            }
            break;
        case KEY_UP:
            if (opt_y > 0) {
                return gain_card_costing_up_to_four(p_interface, p_table, p_player, opt_y - 1);
            }
            break;
        case 'q':
            return;
        default:
            break;
    }
    return gain_card_costing_up_to_four(p_interface, p_table, p_player, opt_y);
}

void trash_up_to_four_cards(interface * p_interface, player * p_player, int8_t opt_y, int8_t trashes) {
    /* Base case */
    if (trashes == 0) {
        clear();
        return;
    }

    /* Prevent player from scanning too far down the list */
    if (opt_y >= p_player->hand->card_count) {
        return trash_up_to_four_cards(p_interface, p_player, opt_y - 1, trashes);
    }

    /* Show status */
    mvprintw(p_interface->bottom_y - 1, 0, "Press 'q' to end trashes");
    mvprintw(p_interface->bottom_y , 0, "Trashes remaining: %d", trashes);

    /* Show hand */
    int16_t y = (p_interface->center_y / 3);
    int16_t x = (p_interface->center_x / 2) - 8;
    mvprintw(y++, x, "HAND");
    for (int8_t i = 0; i < p_player->hand->card_count; ++i) {
        card * p_card = p_player->hand->cards[i];
        if (i == opt_y) {
            attron(COLOR_PAIR(BLACK_ON_WHITE));
        }
        mvprintw(y++, x, "%-10s", p_card->name);
        attroff(COLOR_PAIR(BLACK_ON_WHITE));
    }

    int16_t c = getch();
    switch (c) {
        case 10:
        case 13:
            /* Erase where the word was */
            mvprintw((p_interface->center_y / 3) + p_player->hand->card_count, (p_interface->center_x / 2) - 8, "          ");
            /* Pop card from hand */
            card * p_card = pop_card_at(opt_y, p_player->hand);
            /* Trashing cards frees up memory too */
            p_card = NULL;
            free(p_card);
            return trash_up_to_four_cards(p_interface, p_player, opt_y, trashes - 1);
        case 'q':
            clear();
            return;
        case KEY_DOWN:
            if (opt_y < p_player->hand->card_count - 1) {
                return trash_up_to_four_cards(p_interface, p_player, opt_y + 1, trashes);
            }
        case KEY_UP:
            if (opt_y > 0) {
                return trash_up_to_four_cards(p_interface, p_player, opt_y - 1, trashes);
            }
        default:
            break;
    }
    return trash_up_to_four_cards(p_interface, p_player, opt_y, trashes);
}

void each_other_player_draws_card(table * p_table) {
    for (int8_t i = 0; i < p_table->player_count; ++i) {
        if (i != p_table->turn) {
            draw(p_table->players[i]);
        }
    }
}

int8_t gain_gold(player * p_player, table * p_table) {
    pop_and_push(p_player->discard, p_table->supply_piles[GOLD]);
    card ** golds = (card **)realloc(p_table->supply_piles[GOLD]->cards, p_table->supply_piles[GOLD]->card_count * sizeof(card *));
    if (golds == NULL) {
        return 0;
    } else {
        p_table->supply_piles[GOLD]->cards = golds;
        return 1;
    }
}

int8_t gain_silver_to_deck(player * p_player, table * p_table) {
    pop_and_push(p_player->deck, p_table->supply_piles[SILVER]);
    card ** silvers = (card **)realloc(p_table->supply_piles[SILVER]->cards, p_table->supply_piles[SILVER]->card_count * sizeof(card *));
    if (silvers == NULL) {
        return 0;
    } else {
        p_table->supply_piles[SILVER]->cards = silvers;
        return 1;
    }
}

void each_other_player_gains_curse(table * p_table) {
    for (int8_t i = 0; i < p_table->player_count; ++i) {
        if (i != p_table->turn) {
            pop_and_push(p_table->players[i]->discard, p_table->supply_piles[0]);
        }
    }
}
