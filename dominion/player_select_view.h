#ifndef PLAYER_SELECT_VIEW_H_
#define PLAYER_SELECT_VIEW_H_

#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <ctype.h>
#include "definitions.h"
#include "interface.h"

int player_select_view(struct interface * p_interface, int * player_count, int * player_types, char * names);
void select_player_count(struct interface * p_interface, int * player_count, int option);
void human_or_cpu(struct interface * p_interface, int player_count, int * player_types, int option);
void enter_names(struct interface * p_interface, int player_count, int player_types, char * names, int option, int pos);

#endif
