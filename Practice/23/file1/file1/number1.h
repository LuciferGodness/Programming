#pragma once 
int factorial(int n)
{
	int c = 1;
	for (int i = 1; i <= n; i++)
     c = c * i;
	 return c;
}

