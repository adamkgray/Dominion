#include "render.h"

void render_title(interface * p_interface) {
    int16_t y = (p_interface->center_y / 2) - 1;
    int16_t x = p_interface->center_x - 6;
    mvprintw(y++, x, "*----------*");
    mvprintw(y++, x, "| DOMINION |");
    mvprintw(y++, x, "*----------*");
    x -= 8;
    ++y;
    mvprintw(y++, x, "C implementation by Adam Gray");
    ++y;
    x += 2;
    mvprintw(y, x, "Press any key to continue");
    getch();
    clear();
}

void render_hand(interface * p_interface, player * p_player, int8_t opt_y) {
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
}

void render_supply_piles(interface * p_interface, table * p_table, int8_t opt_y) {
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
}

void render_play_area(interface * p_interface, player * p_player) {
    int16_t y = (p_interface->center_y / 3);
    int16_t x = (p_interface->center_x - 8);
    mvprintw(y++, x, "PLAY AREA");
    for (int8_t i = 0; i < p_player->play_area->card_count; ++i) {
        card * p_card = p_player->play_area->cards[i];
        mvprintw(y++, x, "%-10s", p_card->name);
    }
}

void clear_play_area(interface * p_interface, player * p_player) {
    int16_t y = (p_interface->center_y / 3);
    int16_t x = (p_interface->center_x - 8);
    for (int8_t i; i < p_player->play_area->limit; ++i) {
        mvprintw(y++, x, "          ");
    }
}

void render_status(interface * p_interface, table * p_table, player * p_player, char * phase) {
    mvprintw(p_interface->bottom_y - 1, 0, "Press 'q' to end current phase");
    mvprintw(
        p_interface->bottom_y,
        0,
        "player: %s | phase: %s | actions: %d | buys: %d | $%d",
        p_player->name,
        phase,
        p_player->actions,
        p_player->buys,
        p_table->play_area_value
    );
}

void render_discard(interface * p_interface, player * p_player, int8_t opt_y) {
    int16_t y = (p_interface->center_y / 3);
    int16_t x = (p_interface->center_x - 8);
    mvprintw(y++, x, "DISCARD");
    for (int8_t i = 0; i < p_player->discard->card_count; ++i) {
        card * p_card = p_player->discard->cards[i];
        if (opt_y == i) {
            attron(COLOR_PAIR(BLACK_ON_WHITE));
        }
        mvprintw(y++, x, "%-10s", p_card->name);
        attroff(COLOR_PAIR(BLACK_ON_WHITE));
    }
}

void render_table(interface * p_interface, table * p_table, player * p_player, char * phase) {
    render_status(p_interface, p_table, p_player, phase);
    render_hand(p_interface, p_player, 0);        /* Begin highlighting at index 0 */
    render_play_area(p_interface, p_player);
    render_supply_piles(p_interface, p_table, -1); /* Disable highlighting on supply piles when this function is called */
}
