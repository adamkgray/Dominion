#include "title_screen.h"

void title_screen(struct interface * p_interface) {
    int y = (p_interface->center_y / 2) - 1;
    int x = p_interface->center_x - 6;
    attron(COLOR_PAIR(BLUE_ON_WHITE));
    mvprintw(y++, x, "*----------*");
    mvprintw(y++, x, "| DOMINION |");
    mvprintw(y++, x, "*----------*");
    attroff(COLOR_PAIR(BLUE_ON_WHITE));
    x -= 8;
    ++y;
    mvprintw(y++, x, "C implementation by Adam Gray");
    ++y;
    x += 2;
    mvprintw(y, x, "Press any key to continue");
    getch();
}
