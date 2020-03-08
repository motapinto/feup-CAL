#include <iostream>
#include <vector>

using namespace std;

// Supposing that coins and stock is ordered
vector<int> calcChangeGreedy(int valor, vector<int> coins, vector<int> stock) {
    int montante = valor;
    vector<int> selected;

    if(coins.size() != stock.size()) {
        return selected;
    }

    for (int i = coins.size() - 1; i >= 0 && montante > 0; i--) {
        if(stock.at(i) > 0 && coins.at(i) <= montante) {
            //Choses how many coins to take for each value
            int howMany = min(stock.at(i), montante/coins.at(i));
            // Stores how many coins for each coin value
            selected.push_back(howMany);
            // Changes amount left
            montante -= howMany*coins.at(i);
        }
    }
    return selected;
}

int main() {
    vector<int> values = {1, 2, 5, 10, 15};
    vector<int> stock = {3, 4, 2, 1, 2};
    calcChangeGreedy(8, values, stock);
}