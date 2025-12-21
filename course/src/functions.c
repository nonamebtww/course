#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../headers/models.h"

/**
 * @brief Вычисляет значение функции f(x) по частично заданной формуле.
 *
 * Функция определена по частям:
 * - Если `x < -1`, возвращается  \f$ e^{(-x)^2 - 1} / x^2 \f$.
 * - Если `-1 <= x < 6`, возвращается  \f$ x \cdot \sin(\sqrt{1 + x^2}) \f$.
 * - Если `x >= 6`, возвращается  \f$ \ln(7x^2 - 4x + 8) \f$.
 *
 * @param x Точка, в которой вычисляется значение функции.
 * @return Значение функции в точке @ref x.
 */
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

/**
 * @brief Формирует массив пар (x, f(x)) на заданном интервале.
 *
 * Функция создает динамический массив структур ::MapEntry, где каждая пара
 * содержит значение аргумента `x` и результат вызова функции @ref f.
 *
 * @param start Начальное значение интервала.
 * @param end Конечное значение интервала.
 * @param step Шаг изменения аргумента. Не должен быть равен нулю.
 * @param count Указатель, в который будет записано количество элементов.
 * @return Указатель на динамически выделенный массив структур ::MapEntry,
 *         либо `NULL` в случае ошибки (недопустимый шаг, ошибка выделения памяти).
 */
MapEntry* interval(double start, double end, double step, size_t* count) {
    if (step == 0) {
        return NULL;
    }

    *count = (size_t)ceil(fabs((end - start) / step));
    MapEntry* result = (MapEntry*)malloc(*count * sizeof(MapEntry));

    if (!result) {
        return NULL;
    }

    double x = start;
    for (size_t i = 0; i < *count; x += step, i++) {
        if ((step > 0 && x > end) || (step < 0 && x < end)) {
            break;
        }

        result[i].key = x;
        result[i].value = f(x);
    }

    return result;
}

/**
 * @brief Вычисляет приближённое значение определённого интеграла функции @ref f
 *        методом трапеций.
 *
 * @param lowest_limit Нижний предел интегрирования.
 * @param highest_limit Верхний предел интегрирования.
 * @param count_steps Количество разбиений (число трапеций).
 * @return Приближённое значение интеграла на заданном интервале.
 */
double integral(double lowest_limit, double highest_limit, int count_steps) {
    if (count_steps <= 0) {
        return NAN;
    }
    if (isnan(lowest_limit) || isnan(highest_limit)) {
        return NAN;
    }
    if (isinf(lowest_limit) || isinf(highest_limit)) {
        return NAN;
    }

    double h = (highest_limit - lowest_limit) / count_steps;
    double sum = 0.5 * (f(lowest_limit) + f(highest_limit));

    for (int i = 1; i < count_steps; i++) {
        sum += f(lowest_limit + i * h);
    }

    return sum * h;
}

/**
 * @brief Вычисляет приближённую производную функции @ref f в точке.
 *
 * Используется симметричная разностная формула:
 * \f[
 * f'(x) \approx \frac{f(x+\varepsilon) - f(x-\varepsilon)}{2\varepsilon}
 * \f]
 *
 * @param x Точка, в которой вычисляется производная.
 * @param eps Малое смещение (шаг для численного дифференцирования).
 * @return Приближённое значение производной функции в точке @ref x.
 */
double derivative(double x, double eps) {
    if (eps == 0 || isnan(eps) || isinf(eps)) {
        return NAN;
    }
    if (isnan(x) || isinf(x)) {
        return NAN;
    }

    return (f(x + eps) - f(x - eps)) / (2 * eps);
}