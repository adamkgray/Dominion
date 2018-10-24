#include "title_view.h"

void title_view(interface * p_interface) {
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
