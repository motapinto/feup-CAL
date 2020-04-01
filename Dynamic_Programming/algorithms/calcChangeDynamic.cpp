#include <iostream>
#include <string>

using namespace std;

// Supposing that coins and stock is ordered
string calcChangeDynamic(int m, int numCoins, int *coinValues)
{
    int minCoins[m+1];
    int lastCoin[m+1];

    //Cannot initialize variable-sized object
    for(int i = 0; i <= m; i++) {
        minCoins[i] = 0;
        lastCoin[i] = 0;
    }

    for (int i = 0; i < numCoins; i++) {
        for (int k = 0; k <= m; k++) {
            if ((coinValues[i] <= k) && ( minCoins[k] > minCoins[k - coinValues[i]] + 1 || minCoins[k] == 0)) {
                // Updates new value
                minCoins[k] = minCoins[k - coinValues[i]] + 1;
                // Stores last coin
                lastCoin[k] = coinValues[i];
            }
        }
    }

    // Arrange return result
    string ret_string;
    for (int total = m; total > 0; total -= lastCoin[total]) {
        ret_string += to_string(lastCoin[total]) + " ; ";

        if (lastCoin[total] == 0) {
            ret_string = "-";
            break;
        }
    }
    return ret_string;
}

int main() {
    int values[] = {1, 2, 5, 10, 15};
    cout << "Change = 8 " << endl;
    cout << "Coins: " << calcChangeDynamic(8, 5, values);
}

