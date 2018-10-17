#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <stdlib.h>
#include "table.h"
#include "phases.h"
#include "definitions.h"

struct table * gameplay(struct table * p_table);
int end_conditions(struct table * p_table);

#endif
