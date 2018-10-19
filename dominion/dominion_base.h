#ifndef BASE_SET_H_
#define BASE_SET_H_

#include <stdlib.h>
#include <stdint.h>
#include "definitions.h"
#include "cards.h"
#include "randomize.h"

card_stack ** base_set();
card_stack ** select_playing_cards(card_stack ** base_set);

#endif
