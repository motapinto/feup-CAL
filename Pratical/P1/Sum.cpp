/*
 * Sum.cpp
 */

#include "Sum.h"

string calcSum(int* sequence, int size)
{
    int sum = 0, sumPrev = 0;
    int startIndex = 0;
    string result = "";

    for(int m=1; m<=size; m++) {
        for(int i=0; i<=(size-m); i++) {
            for(int j=i; j<(i+m); j++) {
                sum += sequence[j];
            }
            if(i == 0 || sum < sumPrev) {
                sumPrev = sum;
                startIndex = i;
            }
            sum = 0;
        }
        result += to_string(sumPrev) + "," + to_string(startIndex) + ";";
        sum = 0;
    }

    return result;
}