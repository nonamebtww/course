#pragma once

#include "models.h"

double f(double x);

MapEntry* interval(double start, double end, double step, size_t* size);

double integral(double lowest_limit, double highest_limit, int count_steps);

double derivative(double x, double eps);