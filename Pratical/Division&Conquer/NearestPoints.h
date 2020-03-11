
#ifndef UTIL_H_
#define UTIL_H_

#include "Point.h"

/*
 * Auxiliary class to store a solution.
 */
class Result {
public:
	double dmin; // distance between selected points
	Point p1, p2; // selected points
	Result(double dmin2, Point p1, Point p2);
	Result();
};

/*
 * Retorna um objeto com os pontos mais próximos pertencentes ao vetor vp e a distância entre eles.
 * Implemente esta função com um algoritmo de força bruta, corra os testes e o tempo necessário para
 * as pesquisas. Verifique se o tempo é aproximadamente quadrático O(N2) no tamanho dos dados.
*/
Result nearestPoints_BF(vector<Point> &vp);

/*
 * Seguindo um algoritmo de divisão e conquista como o descrito mais abaixo
 * (mas sem implementar a parte final que obriga a ter duas listas). Implemente
 * a função, execute os testes e compare os tempos de execução com os da alínea a. Verifique se o
 * tempo é aproximadamente O(N log2 N) no tamanho dos dados
 *
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp);
Result nearestPoints_DC(vector<Point> &vp);
Result nearestPoints_DC_MT(vector<Point> &vp);
void setNumThreads(int num);

// Pointer to function that computes nearest points
typedef Result (*NP_FUNC)(vector<Point> &vp);



#endif