#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#if defined(_WIN32)
#include <conio.h>
#endif


#include "menu.h"
#include "functions.h"
#include "logging.h"
#include "models.h"

void menu() {
    int action;

    do
    {
        action = -1;

        printf("1. Значение - f(x) в точке\n");
        printf("2. Таблица - x → f(x) на интервале\n");
        printf("3. Вычисление определенного интеграла\n");
        printf("4. Производная - f'(x) в точке\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &action);

        switch (action) {
            case 1:
                process_function();
                break;
            case 2:
                process_interval();
                break;
            case 3:
                process_integral();
                break;
            case 4:
                process_derivative();
                break;
            case 0:
                return;

            default:
                log_error("неизвестное действие. Повторите.\n");
                break;
        }

        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {}

#if defined(_WIN32)
        printf("\nНажмите любую клавишу для продолжения\n");
        (void)_getch();

        system("cls");
#else
        printf("\nНажмите Enter для продолжения\n");
        while ((ch = getchar()) != '\n' && ch != EOF) {}

        system("clear");
#endif
    } while (1);
}

void process_function() {
    double x;

    printf("Введите x: ");
    if (scanf("%lf", &x) != 1) {
        log_error("Ошибка ввода: ожидалось число.");
        return;
    }

    double result = f(x);
    if (isnan(result)) {
        log_error("Ошибка вычисления f(x): некорректные входные данные.");
        return;
    }

    printf("f(x) = %lf\n", result);
}

void process_interval() {
    double a, b, c;

    printf("Введите начало: ");
    if (scanf("%lf", &a) != 1) {
        log_error("Ошибка ввода: ожидалось число.");
        return;
    }

    printf("Введите конец: ");
    if (scanf("%lf", &b) != 1) {
        log_error("Ошибка ввода: ожидалось число.");
        return;
    }

    printf("Введите шаг: ");
    if (scanf("%lf", &c) != 1) {
        log_error("Ошибка ввода: ожидалось число.");
        return;
    }

    MapEntry* map;
    size_t size;
    map = interval(a, b, c, &size);

    if (map == NULL) {
        log_error("Неправильный ввод. Не удалось вычислить значения.");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%lf | %lf\n", map[i].key, map[i].value);
    }

    free(map);
}

void process_integral() {
    double a, b;
    int c;

    printf("Введите нижний предел: ");
    if (scanf("%lf", &a) != 1) {
        log_error("Ошибка ввода: ожидалось число.");
        return;
    }

    printf("Введите верхний предел: ");
    if (scanf("%lf", &b) != 1) {
        log_error("Ошибка ввода: ожидалось число.");
        return;
    }

    printf("Введите количество шагов: ");
    if (scanf("%d", &c) != 1) {
        log_error("Ошибка ввода: ожидалось целое число.");
        return;
    }

    double result = integral(a, b, c);
    if (isnan(result)) {
        log_error("Ошибка вычисления интеграла: некорректные входные данные.");
        return;
    }

    printf("Интеграл: %lf\n", result);
}

void process_derivative() {
    double x, eps;

    printf("Введите x: ");
    if (scanf("%lf", &x) != 1) {
        log_error("Ошибка ввода: ожидалось число.");
        return;
    }

    printf("Введите точность: ");
    if (scanf("%lf", &eps) != 1) {
        log_error("Ошибка ввода: ожидалось число.");
        return;
    }

    double result = derivative(x, eps);
    if (isnan(result)) {
        log_error("Ошибка вычисления производной: некорректные входные данные.");
        return;
    }

    printf("Производная: %lf\n", result);
}
