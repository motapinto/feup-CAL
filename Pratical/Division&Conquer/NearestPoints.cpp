/*
 * NearestPoints.cpp
 */

#include <limits>
#include <thread>
#include <algorithm>
#include <cmath>
#include "NearestPoints.h"
#include "Point.h"

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
 * Auxiliary function to sort vector of points by X axis.
 */
static void sortByX(vector<Point> &v, int left, int right) {
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.x < q.x || (p.x == q.x && p.y < q.y); });
}

/**
 * Auxiliary function to sort vector of points Y axis.
 */
static void sortByY(vector<Point> &v, int left, int right) {
	std::sort(v.begin( ) + left, v.begin() + right + 1,
		[](Point p, Point q){ return p.y < q.y || (p.y == q.y && p.x < q.x); });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point> &vp) {
    Result res;
	for(int i = 0; i < vp.size(); i++) {
	    for(int j = i + 1; j < vp.size(); j++) {
	        if(vp.at(i).distance(vp.at(j)) < res.dmin) {
	            res.dmin = abs(vp.at(i).distance(vp.at(j)));
	            res.p1 = vp.at(i);
	            res.p2 = vp.at(j);
	        }
	    }
	}
	return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point> &vp) {
	Result res;
	sortByX(vp, 0, vp.size()-1);

    for(int i = 0; i < vp.size(); i++) {
        for(int j = i + 1; j < vp.size(); j++) {
            if(vp.at(i).distance(vp.at(j)) < res.dmin) {
                res.dmin = abs(vp.at(i).distance(vp.at(j)));
                res.p1 = vp.at(i);
                res.p2 = vp.at(j);
            }
        }
    }
	return res;
}

/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 * This function is brute force but only is used for the strip
 */
static void npByY(vector<Point> &vp, int left, int right, Result &res) {
    for (int i = left; i <= right; i++) {
        for (int j = i+1; j <= right; j++) {
            if (abs(vp.at(j).y - vp.at(i).y) >= res.dmin) {
                break;
            }
            else if (vp.at(i).distance(vp.at(j)) < res.dmin){
                res.p1 = vp.at(i);
                res.p2 = vp.at(j);
                res.dmin = vp.at(i).distance(vp.at(j));
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
    Result res;

    // Base case of two points
    if (right - left == 1) {
        return Result(vp.at(left).distance(vp.at(right)), vp.at(left), vp.at(right));
    }

    // Base case of a single point: no solution, so distance is MAX_DOUBLE
    if (right == left) {
        return Result(MAX_DOUBLE, vp.at(left), vp.at(right));
    }

	// Divide in halves (left and right) and solve them recursively,
	// possibly in parallel (in case numThreads > 1)
	int middle = (right + left) / 2;
	Result leftRes = np_DC(vp, left, middle, numThreads);
	Result RightRes = np_DC(vp, left, middle + 1, numThreads);

	// Select the best solution from left and right
    Result best = leftRes.dmin > RightRes.dmin ? RightRes : leftRes;

    // Determine the strip area around middle point
    double midX = (vp.at(middle).x + vp.at(middle + 1).x) / 2;
    int leftStrip = middle;
    int RightStrip = middle + 1;
    // See how many points is is the strip
    for (; vp.at(leftStrip - 1).x > midX - res.dmin && leftStrip > left; leftStrip--);
    for (; vp.at(RightStrip + 1).x < midX + res.dmin && RightStrip < right; RightStrip++);

	// Order points in strip area by Y coordinate
    sortByY(vp, leftStrip, RightStrip);

    // Calculate nearest points in strip area (using npByY function)
    npByY(vp, leftStrip, RightStrip, best);

    // Reorder points in strip area back by X coordinate
    sortByX(vp, leftStrip, RightStrip);

    return best;
}

/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num) {
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
