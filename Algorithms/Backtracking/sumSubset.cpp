#include <stdio.h> 
#include <stdlib.h> 
 
// prints subset found 
void printSubset(int A[], int size) { 
	for(int i = 0; i < size; i++) { 
		printf("%*d", 5, A[i]); 
	} 

	printf("\n"); 
} 

//subset_sum(values, tuple, size, t_size, sum, ite, targetSum); 
// sum - sum so far     |     ite - nodes count 

static int total_nodes;
void subsetSum(int values[], int tuple[], int size, int t_size, int sum, int ite, int target_sum) { 
	total_nodes++; 
    printf("Current sum: %d\n", sum);
	if( target_sum == sum ) { 
		// We found subset 
		printSubset(tuple, t_size); 
		// Exclude previously added item and consider next candidate (can be more than one tuple)
		subsetSum(values, tuple, size, t_size-1, sum - values[ite], ite + 1, target_sum); 
		return; 
	} else { 
		// generate nodes along the breadth 
		for( int i = ite; i < size; i++ ) { 
			tuple[t_size] = values[i]; 
			// consider next level node (along depth) 
			subsetSum(values, tuple, size, t_size + 1, sum + values[i], i + 1, target_sum); 
		} 
	} 
} 

void subsetSumPromissing(int values[], int tuple[], int size, int t_size, int sum, int index, int target_sum) { 
	total_nodes++;
    // Found a subset and should exclude  previously added item and consider next candidate (can be more than one tuple)
    if( target_sum == sum ) { 
		printSubset(tuple, t_size); 
		subsetSumPromissing(values, tuple, size, t_size-1, sum - values[index], index + 1, target_sum); 

	} else { 
		// generate nodes along the breadth 
		for( int i = index; i < size; i++ ) { 
			tuple[t_size] = values[i]; 
            // if next node is promissing
            if(index < size && tuple[t_size] + sum <= target_sum) {
			    // consider next level node (along depth) 
			    subsetSumPromissing(values, tuple, size, t_size + 1, sum + values[i], i + 1, target_sum);
            }
	    } 
    }
} 

void generateSubsets(int values[], int size, int targetSum) { 
    // allocates memory for a vector
	int *tuplet_vector = (int *)malloc(size * sizeof(int)); 
    //subset_sum(values, tuplet_vector, size, t_size, sum, ite, 0, targetSum); 
    //subsetSum(values, tuplet_vector, size, 0, 0, 0, targetSum); 
    subsetSumPromissing(values, tuplet_vector, size, 0, 0, 0, targetSum); 
    // frees the memory
	free(tuplet_vector); 
} 

int main() { 
	int weights[] = {3, 4, 5, 6}; 
    int sum = 13, n = 4;

	generateSubsets(weights, n, sum); 
	
    printf("Nodes generated: %d\n", total_nodes); 
	return 0; 
} 
