#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "functions.h"


int main() {
	setlocale(LC_ALL, "RUS");

	int action;
	double x, a, b, c;

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
			printf("Введите x: ");
			scanf("%lf", &x);

			printf("f(x) = %lf\n", f(x));
			break;
		case 2:
			printf("Введите начало: ");
			scanf("%lf", &a);

			//
			printf("Введите конец: ");
			scanf("%lf", &b);

			//
			printf("Введите шаг: ");
			scanf("%lf", &c);

			//
			interval(a, b, c);
			printf("\n");
			break;
		case 3:
			printf("Введите нижний предел: ");
			scanf("%lf", &a);

			//
			printf("Введите верхний предел: ");
			scanf("%lf", &b);

			//
			printf("Введите количество шагов: ");
			scanf("%lf", &c);

			//
			printf("Интеграл: %lf\n", integral(a, b, c));
			break;
		case 4:
			printf("Введите x: ");
			scanf("%lf", &x);

			//
			printf("Введите точность: ");
			scanf("%lf", &c);

			//
			printf("Производная: %lf\n", derivative(x, c));
			break;
		case 0:
			return 0;
		}

		printf("Нажмите любую клавишу для продолжения");
		getchar();

#if defined(_WIN32)
		system("cls");
#else
		system("clear");
#endif
	} while (1);
}