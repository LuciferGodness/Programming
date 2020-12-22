#ifndef NUMBER3_H
#define NUMBER3_H
#include"number1.h"
int combinations(int t, int b)
{
	int comb;
	comb = factorial(b) / (factorial(t) * factorial(b-t));
	return comb;
}
#endif
