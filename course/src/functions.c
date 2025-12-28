#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../headers/models.h"

double f(double x) {
    if (isnan(x) || isinf(x)) {
        return NAN;
    }

    if (x < -1) {
        if (x == 0) {
            return NAN;
        }

        return (exp(-pow(x, 2)) - 1) / pow(x, 2);
    }

    if (x < 6) {
        return x * sin(sqrt(1 + pow(x, 2)));
    }

    double expr = 7 * pow(x, 2) - 4 * x + 8;

    if (expr <= 0) {
        return NAN;
    }

    return log(expr);
}

MapEntry* interval(double lowest_limit, double highest_limit, int count_steps) {
    if (count_steps <= 0) {
        return NULL;
    }
    if (isnan(lowest_limit) || isnan(highest_limit)) {
        return NULL;
    }
    if (isinf(lowest_limit) || isinf(highest_limit)) {
        return NULL;
    }

    double h = (highest_limit - lowest_limit) / count_steps;
    size_t points = (size_t)count_steps + 1;
    MapEntry* result = (MapEntry*)malloc(points * sizeof(MapEntry));

    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < points; i++) {
        double x = lowest_limit + i * h;
        result[i].key = x;
        result[i].value = f(x);
    }

    return result;
}

MapEntry* integral(double lowest_limit, double highest_limit, int count_steps) {
    if (count_steps <= 0) {
        return NULL;
    }
    if (isnan(lowest_limit) || isnan(highest_limit)) {
        return NULL;
    }
    if (isinf(lowest_limit) || isinf(highest_limit)) {
        return NULL;
    }

    if (count_steps % 2 != 0) {
        count_steps++;
    }

    double eps = (highest_limit - lowest_limit) / count_steps;
    double sum = f(lowest_limit) + f(highest_limit);

    for (int i = 1; i < count_steps; ++i) {
        double x = lowest_limit + i * eps;

        if (i % 2 == 0) {
            sum += 2 * f(x);
        }
        else {
            sum += 4 * f(x);
        }
    }

    double result_value = sum * (eps / 3.0);
    MapEntry* me = (MapEntry*)malloc(sizeof(MapEntry));

    if (!me) {
        return NULL;
    }

    me->key = lowest_limit;
    me->value = result_value;

    return me;
}

MapEntry* derivative(double lowest_limit, double highest_limit, int count_steps) {
    if (count_steps <= 0) {
        return NULL;
    }
    if (isnan(lowest_limit) || isnan(highest_limit)) {
        return NULL;
    }
    if (isinf(lowest_limit) || isinf(highest_limit)) {
        return NULL;
    }

    double eps = (highest_limit - lowest_limit) / count_steps;
    if (eps == 0 || isnan(eps) || isinf(eps)) {
        return NULL;
    }

    double x = lowest_limit;
    if (isnan(x) || isinf(x)) {
        return NULL;
    }

    double result_value = (f(x + eps) - f(x - eps)) / (2 * eps);
    MapEntry* result = (MapEntry*)malloc(sizeof(MapEntry));

    if (!result) {
        return NULL;
    }

    result->key = x;
    result->value = result_value;

    return result;
}