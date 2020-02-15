#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/* Calcula o troco num determinado montante m, utilizando um numero minimo
 * de moedas de valores unitarios indicados (coinValues).
 * O array coinValues deve estar ordenado por ordem crescente.
 * O parametro numCoins indica o tamanho do array.
 * Devolve:
 * Uma string com a sequencia de valores das moedas por valores decrescente.
 * Por exemplo: calcChange(9, 3, {1, 2, 5}) = "5;2;2;"
 */
string calcChange(int m, int numCoins, int *coinValues);

//Greedy algorithm
string calChangeGreedy(int m, int numCoins, int *coinValues);