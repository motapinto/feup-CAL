#include "Labirinth.h"

Labirinth::Labirinth(int values[10][10]) {
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            this->labirinth[i][j] = values[i][j];
        }
	}
	this->initializeVisited();
}

void Labirinth::initializeVisited() {
	for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            this->visited[i][j] = false;
        }
	}
}

void  Labirinth::printLabirinth() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
            cout << labirinth[i][j] << " ";
		}
		cout << endl;
	}
}

bool Labirinth::findGoal(int x, int y) {
    if (x < 0 || y < 0 || x >= 10 || x >= 10 || this->labirinth[x][y] == 0 || this->visited[x][y]) {
        return false;
    } else if(this->labirinth[x][y] == 2) {
        cout << endl << "Reached the exit in x:" << x << " y:" << y << endl;
        return true;
    } else {
        this->visited[x][y] = true;
    }

    return (this->findGoal(x+1, y) || this->findGoal(x-1, y) || this->findGoal(x, y+1) || this->findGoal(x, y-1));
}