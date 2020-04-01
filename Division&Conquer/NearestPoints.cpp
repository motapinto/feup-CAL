/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

Result result;
const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
	this->dmin = dmin;
	this->p1 = p1;
	this->p2 = p2;
}

Result::Result() {
	this->dmin = MAX_DOUBLE;
	this->p1 = Point(0,0);
	this->p2 = Point(0,0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

static void sortByY(vector<Point> &v, int left, int right)
{
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
	Result res;

    for (auto p1 = vp.begin(); p1 != vp.end(); p1++) {
        for (auto p2 = p1 + 1; p2 != vp.end(); p2++) {
            double distSqr = p1->distSquare(*p2);
            if(distSqr < res.dmin){
                res.dmin = distSqr;
                res.p1 = *p1;
                res.p2 = *p2;
            }
        }
    }

    res.dmin = sqrt(res.dmin);
	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);

    for (auto p1 = vp.begin(); p1 != vp.end(); p1++) {
        for (auto p2 = p1 + 1; p2 != vp.end(); p2++) {
            double distSqr = p1->distSquare(*p2);
            if(distSqr < res.dmin){
                res.dmin = distSqr;
                res.p1 = *p1;
                res.p2 = *p2;
            }
        }
    }

    res.dmin = sqrt(res.dmin);
	return res;
}


/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res)
{

    int diff = right - left;
    for (auto p1 = vp.begin() + left; p1 + diff != vp.end(); p1++) {
        for (auto p2 = p1 + 1; p2 + diff != vp.end(); p2++) {
            if(p2->y - p1->y > res.dmin){
                break;
            }
            double distance = p1->distance(*p2);
            if(distance < res.dmin){
                res.dmin = distance;
                res.p1 = *p1;
                res.p2 = *p2;
            }
        }
    }
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point> &vp, int left, int right, int numThreads) {
    Result res = Result();

    // Base case of two points
    if((right - left) == 1){
        res.p1 = vp[right];
        res.p2 = vp[left];
        res.dmin = res.p1.distance(res.p2);
        return res;
    }

	// Base case of a single point: no solution, so distance is MAX_DOUBLE
	if(right <= left){
        return res;
	}

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	int middle = (right + left) / 2;
    Result res1, res2 = res1 = Result();
    if(numThreads > 1){
        thread thread_calculator([](vector<Point> vp, int left, int right, int numThreads) {
            result = np_DC(vp, left, right, numThreads);
        },
                vp, left, middle, numThreads >> 1);

        res2 = np_DC(vp, middle + 1, right, numThreads >> 1);
        thread_calculator.join();
        res1 = result;
    } else {
        res1 = np_DC(vp, left, middle, numThreads);
        res2 = np_DC(vp, middle + 1, right, numThreads);
    }

	// Select the best solution from left and right
	res = res1.dmin < res2.dmin ? res1 : res2;

	// Determine the strip area around middle point
	double middle_x = (vp[middle].x + vp[middle + 1].x) / 2;
    double x_left = middle_x - res.dmin;
    double x_right = middle_x + res.dmin;

    for (int i = left; i <= middle; i++) {
        if(vp[i].x >= x_left){
            left = i;
            break;
        }
    }

    for (int i = right; i > middle; i--) {
        if(vp[i].x <= x_right) {
            right = i;
            break;
        }
    }

	// Order points in strip area by Y coordinate
    sortByY(vp, left, right);

	// Calculate nearest points in strip area (using npByY function)
    npByY(vp, left, right, res);

	// Reorder points in strip area back by X coordinate
	sortByX(vp, left, right);

	return res;
}

/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num)
{
	numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, 1);
}


/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point> &vp) {
	sortByX(vp, 0, vp.size() -1);
	return np_DC(vp, 0, vp.size() - 1, numThreads);
}
