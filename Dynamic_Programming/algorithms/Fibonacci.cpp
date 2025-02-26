#include "Fibonacci.h" 

int fibonacciRecursive(int n) {
    if(n == 0 || n == 1)
        return n;
    else
        return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int fibonacciDynamic(int n) {
    int fib[n+1];
    fib[0] = 0;
    fib[1] = 1;

    for(int i = 2; i<=n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    return fib[n];
}