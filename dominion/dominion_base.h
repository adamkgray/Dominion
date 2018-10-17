#ifndef BASE_SET_H_
#define BASE_SET_H_

#include <stdlib.h>
#include "definitions.h"
#include "cards.h"
#include "randomize.h"

struct card_stack ** base_set();
struct card_stack ** select_playing_cards(struct card_stack ** base_set);

#endif
