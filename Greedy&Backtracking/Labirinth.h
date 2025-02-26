#ifndef LABIRINTH_H_
#define LABIRINTH_H_

#include <iostream>
using namespace std;

class Labirinth {
    private:
        int labirinth[10][10];
        bool visited[10][10];
        void initializeVisited();

    public:
        Labirinth(int values[10][10]);
        void printLabirinth();
        bool findGoal(int x, int y);
};

#endif /* LABIRINTH_H_ */
