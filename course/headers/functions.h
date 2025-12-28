#pragma once

#include "models.h"

double f(double x);

MapEntry* interval(double lowest_limit, double highest_limit, int count_steps);

MapEntry* integral(double lowest_limit, double highest_limit, int count_steps);

MapEntry* derivative(double lowest_limit, double highest_limit, int count_steps);