#include <iostream>

using namespace std; 
  
/*
    W: maximum weight capacity
    wt: weights of each item
    val: values of each item
    n: number of items
*/
int knapSack(int W, int wt[], int val[], int n) {
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
    int val[] = {60, 100, 120}; 
    int wt[] = {10, 20, 30}; 
    int  W = 50; 
    int n = sizeof(val)/sizeof(val[0]); 
    cout << knapSack(W, wt, val, n) << endl;
} 