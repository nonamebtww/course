#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "menu.h"

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");

#if defined(_WIN32)
	system("chcp 1251");
#endif


	menu();
}