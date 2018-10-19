#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <stdint.h>
#include <stdlib.h>
#include "table.h"
#include "phases.h"
#include "interface.h"
#include "definitions.h"

table * gameplay(interface * p_interface, table * p_table);
int8_t end_conditions(table * p_table);

#endif
