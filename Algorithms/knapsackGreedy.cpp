#include <iostream>
#include <vector>
#include <bits/stdc++.h> //for sort()

using namespace std; 
  
/*
    W: maximum weight capacity
    wt: weights of each item
    val: values of each item
    n: number of items
*/

int knapSack(int W, int val[], int wt[], int n) {
    vector<double> density;
    vector<int> selected;
    int totalValue = 0, totalWeight = 0;

    // Stores and order density's of each item
    for(int i = 0; i < n; i++) {
        density.push_back((double)val[i] / wt[i]);
    }

    //Greedy algorithm
    //1)Pick the best
    //2)Discard

    for(int i = 0; i < n; i++) {
        // Picks the best item based on density
        int maxElemIndex = max_element(density.begin(), density.end()) - density.begin();

        if(totalWeight + wt[maxElemIndex] <= W) {
            totalValue += val[maxElemIndex] ;
            totalWeight += wt[maxElemIndex];
            selected.push_back(maxElemIndex);
            i = 0;
        }
   }

    return totalValue;
}

int main() { 
    int  W = 17;
    int val[] = {4, 5, 10, 11, 13}; 
    int wt[] = {3, 4, 7, 8, 9}; 
    int n = sizeof(val)/sizeof(val[0]); 
    cout << knapSack(W, val, wt, n) << endl;
} 