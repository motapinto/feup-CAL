#include <iostream>

using namespace std; 
  
/*
    W: maximum weight capacity
    wt: weights of each item
    val: values of each item
    n: number of items
*/
int knapSack(int W, int val[], int wt[], int n) {
    int cost[W+1];
    int last[W+1];

    // Variable sized arrays cannot be initialized
    for(int i = 0; i <= W; i++) {
        cost[i] = 0;
        last[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        for(int j = wt[i]; j<= W ; j++) {
            // subproblem
            if(val[i] + cost[j - wt[i]] > cost[j]) {
                cost[j] = val[i] + cost[j - wt[i]];
                last[j] = i;
            }
        }
    }
    return cost[W];
}

int main() { 
    int  W = 17;
    int val[] = {4, 5, 10, 11, 13}; 
    int wt[] = {3, 4, 7, 8, 9};
    int n = sizeof(val)/sizeof(val[0]); 
    cout << knapSack(W, val, wt, n) << endl;
} 