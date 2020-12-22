#ifndef NUMBER2_H
#define NUMBER2_H
#include"number1.h"
#include<cmath>
double sin(double x, int k)
{
	for (int i = 1; i <= k; i++)
	  x = x + pow(-1, i) * (pow(x, (2 * i + 1)) / factorial(2 * i + 1));
	return x;
}
#endif
