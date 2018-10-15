#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <stdlib.h>
#include <stdio.h>
#include "table.h"
#include "action_phase.h"
#include "buy_phase.h"
#include "cleanup_phase.h"
#include "end_conditions.h"

struct table * gameplay(struct table * p_table);

#endif
