#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/limits.h>

#include "log.h"
#include "../btree/btree.h"

#define FARL_MAPPINGS_ENVVAR "FARL_MAPPINGS"

void load_mappings(void);
void discard_mappings(void);
char* map_path(char* virtual_path);
