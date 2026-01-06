#pragma once

#include "models.h"

void log_error(const char* message);

int show_interval(MapEntry* entities, size_t size);

int save_interval(MapEntry* entities, size_t size, char* filename);