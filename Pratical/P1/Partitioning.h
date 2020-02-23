/*
 * Partioning.h
 */

#ifndef PARTITIONING_H_
#define PARTITIONING_H_

#include <iostream>

// S(n,k) = S(n-1, k-1) + kS(n-1, k), se 1<k<n
// S(n,k) = 1, se k=1 ou k=n

/*Implementa a função s(n,k) usando recursividade*/
int s_recursive(int n,int k);

/*Implementa a função b(n) usando recursividade*/
int b_recursive(int n);

/*Implementa a função s(n,k) usando programação dinâmica*/
int s_dynamic(int n,int k);

/*Implementa a função b(n) usando programação dinâmica*/
int b_dynamic(int n);

#endif /* SUM_H_ */