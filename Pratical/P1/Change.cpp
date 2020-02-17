/*
 * Change.cpp
 */

#include "Change.h"

//m: troco 
//numCoins: numero de moedas no array de coinValues
//coinValues: moedas disponiveis para dar troco (com stock infinito)

//Dynamic programming approach
string calcChange(int m, int numCoins, int *coinValues)
{
	int minCoin[m + 1];
	int lastCoin[m + 1];
	for (int i = 0; i < m + 1; i++) {
		minCoin[i] = 100;
		lastCoin[i] = 0;
	}
	minCoin[0] = 0;

	for (int i = 0; i < numCoins; i++) {
		int possibleLastCoin = coinValues[i];
		for (int k = 1; k <= m; k++) {
			int remainingChange = k - possibleLastCoin;
			if (remainingChange >= 0) {
				int possibleMinCoin = minCoin[remainingChange] + 1;
				if (possibleMinCoin < minCoin[k]) {
					minCoin[k] = possibleMinCoin;
					lastCoin[k] = possibleLastCoin;
				}
			}
		}
	}

	// printing the result
	for (int k = 0; k <= m; k++)
		cout << k << "    \t";
	cout << endl;
	for (int k = 0; k <= m; k++)
		cout << minCoin[k] << " - " << lastCoin[k] << "\t";

	// getting the result
	int remainingChange = m;
	string answer = "";
	while (remainingChange != 0) {
		answer += to_string(lastCoin[remainingChange]) + ";";
		remainingChange -= lastCoin[remainingChange];
	}
	cout << answer << endl;
	return answer;
}

//Greedy approach (coinValues is ordered)
string calChangeGreedy(int m, int numCoins, int* coinValues) {
    int missingChange;
	string change[100] = {""};

	if (m - coinValues[0] < 0 && m != 0)
		return "-";

	for (int i = 1; i <= m; i++) {
		missingChange = i;
		int j = numCoins - 1;

		while (j >= 0) {
            // if the highest coin value is lower than the missing change ...
			if (missingChange >= coinValues[j]) {
				missingChange -= coinValues[j];
				change[i] = to_string(coinValues[j]) + " ; " + change[missingChange];
				break;
			}
            //else discard highest coin and only consider the subset of coins without the higher one
			else {
				j--;
			}
		}
	}
    return change[m];
}