#include "Sudoku.h"

Sudoku::Sudoku() {
	this->initialize();
}

Sudoku::Sudoku(int nums[9][9]) {
	this->initialize();

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (nums[i][j] != 0) {
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int n = 0; n < 10; n++) {
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

int** Sudoku::getNumbers() {
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++) {
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++) {
            ret[i][a] = numbers[i][a];
		}
	}
	return ret;
}

bool Sudoku::isComplete() {
	return countFilled == 9 * 9;
}

bool Sudoku::solve() {
    if (isComplete()) return true;

    // find best candidate to insert number (cell with less number of candidates)
    int min_candidates = 10;
    int r = 0, c = 0;
    bool found_one = false;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++)  {
            if (numbers[row][col] != 0) {
                continue;
            }
            // Check which numbers can be inserted (number of candidates for each cell)
            int candidates = 0;
            for (int num = 1; num <= 9; num++) {
                if (columnHasNumber[col][num] || lineHasNumber[row][num] || block3x3HasNumber[row/3][col/3][num]) continue;
                candidates++;
            }

            // if found invalid position with current matrix, return false -> backtracks
            if (candidates == 0) return false;

            // updates best cell
            if (candidates < min_candidates)  {
                min_candidates = candidates;
                r = row;
                c = col;
            }
            // no need to continue process
            if (candidates == 1) {
                found_one = true;
                break;
            }
        }
    }

    // insert possible values in found position
    for (int num = 1; num <= 9; num++) {
        if (columnHasNumber[c][num] || lineHasNumber[r][num] || block3x3HasNumber[r/3][c/3][num]) {
            continue;
        }

        // update matrix
        numbers[r][c] = num;
        columnHasNumber[c][num] = true;
        lineHasNumber[r][num] = true;
        block3x3HasNumber[r/3][c/3][num] = true;
        countFilled++;

        if (solve()) {
            return true;
        }

        // if not good guess, go back
        numbers[r][c] = 0;
        columnHasNumber[c][num] = false;
        lineHasNumber[r][num] = false;
        block3x3HasNumber[r/3][c/3][num] = false;
        countFilled--;
    }
    // did not find valid number with current values -> backtracks
    return false;
}

void Sudoku::print() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
            cout << this->numbers[i][j] << " ";
		}
		cout << endl;
	}
}