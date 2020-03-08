# define MAX 100
#include <iostream>
using namespace std;

long long row[MAX + 1]; // initialized with 0's by default if declared globally

int nCrDynamic(int n, int r) {
    int i, j;

    // initialize by the first row
    row[0] = 1; // this is the value of C(0, 0)

    for(i = 1; i <= n; i++) {
        for(j = i; j > 0; j--) {
             // from the recurrence C(n, r) = C(n - 1, r - 1) + C(n - 1, r)
             cout << "row[" << j << "] = " << row[j] << "+" << row[j - 1] << " = " << row[j] + row[j-1] << "   ->   ";
             row[j] += row[j - 1];
             cout << row[j] << endl;;
        }
        cout << "i:" << i << endl << endl;
    }
    return row[r];
}

int main() {
    nCrDynamic(5, 2);
}