#include <stdio.h>
#include <math.h>

#define _USE_MATH_DEFINES


double f(double x) {
	if (x < -1) {
		return (exp(pow(-x, 2) - 1))/pow(x, 2);
	}

	if (x < 6) {
		return x * sin(sqrt(1 + pow(x, 2)));
	}

	return log(7 * pow(x, 2) - 4 * x + 8);
}

void interval(double start, double end, double step) {
	double x;

	for (; start < end; start += step) {
		x = f(start);

		printf("%lf | %lf\n", start, x);
	}
}

double integral(double lowest_limit, double highest_limit, int count_steps) {
	double h = (highest_limit - lowest_limit) / count_steps;
	double sum = 0.5 * (f(lowest_limit) + f(highest_limit));

	for (int i = 1; i < count_steps; i++) {
		sum += f(lowest_limit + i * h);
	}

	return sum * h;
}

double derivative(double x, double eps) {
	return (f(x + eps) - f(x - eps)) / (2 * eps);
}