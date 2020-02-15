#include "Factorial.h"

int factorial(int n) {
    std::cout << "factorial: " << n << std::endl;
    if(n == 1 || n == 0)
        return 1;
    else if(n > 1)
        return factorial(n-1)*n;
    else
        return 0;
}

int factorialDinamic(int n) {
    std::cout << "factorialDinamic: " << n << std::endl;

    if(n < 0)
        return 0;
    int factorials[100] = {0};
    factorials[0] = 1;
    factorials[1] = 1;

    for (int i = 1; i <= n; ++i)
		factorials[i] = i * factorials[i - 1];
	return factorials[n];
} 