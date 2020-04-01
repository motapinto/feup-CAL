/*
 * Sum.h
 */

#ifndef SUM_H_
#define SUM_H_

#include <iostream>
#include <string>
using namespace std;


/* Calcula, numa sequência de n números (n > 0), para cada subsequência de m números (m <= n, m > 0),
 * o índice i a partir do qual a soma s dos valores dessa subsequência é mínimo.
 *
 * Argumentos:
 * 	sequence - Array com a sequência
 * 	size - Tamanho da sequência
 *
 * Devolve:
 * Uma string que contêm com a indicação do índice i e somatório s, para cada m
 * s[0],i[0];s[1],i[1],s[2],i[2]...
 * Exemplo: 1,4;9,1;11,2;18,1;22,0;
 */
string calcSum(int* sequence, int size);

#endif /* SUM_H_ */
