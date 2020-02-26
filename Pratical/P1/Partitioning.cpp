/*
 * Partioning.cpp
 */

#include "Partitioning.h"

int s_recursive(int n, int k)
{
    if(k == 1 || k == n) {
        return 1;
    }

   return (s_recursive(n-1, k-1) + k*s_recursive(n-1, k));
}

int s_dynamic(int n, int k)
{
    int len = n - k + 1; // length of S's needed to calculate
    int values [len]; // stores de values for each k

    // cannot initialize variable sized array
    for (int i = 0; i < len; ++i) {
        values[i] = 1;
    }

    for (int i = 2; i <= k; ++i) { //iterate through k
        for (int j = 1; j < len; ++j) { // since the first value is always equal to zero it starts in the second position
            values[j] = values[j] + i*values[j-1]; //
        }
    }
    return values[len - 1];
}

int b_recursive(int n)
{
    int bSum = 0;

    for (int k = n; k > 0; --k) {
        bSum += s_recursive(n, k);
    }
	return bSum;
}

int b_dynamic(int n)
{
    int values[n]; //A line of S(n,k)
    int sum = 0; //sum of that line

    // cannot initialize variable sized array
    for(int i = 0; i < n; i++) {
        values[i] = 1;
    }

    //computes all lines until i=n
    for (int i = 3; i <= n; ++i) {
        for(int j = i - 1; j > 1; --j) { //for k=n value[k] is always equal to 0
            values[j] = values[j-1] + j*values[j];
        }
    }

    for (int k = 0; k < n; ++k) {
        sum += values[k];
    }
    return sum;
}