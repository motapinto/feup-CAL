/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in);
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    private:
        static const int infinite = 9999999;
        vector<Vertex<T> *> vertexSet;    // vertex set

    public:
        Vertex<T> *findVertex(const T &in) const;
        bool addVertex(const T &in);
        bool addEdge(const T &sourc, const T &dest, double w);
        int getNumVertex() const;
        vector<Vertex<T> *> getVertexSet() const;

        void unweightedShortestPath(const T &s);    //TODO...
        void dijkstraShortestPath(const T &s);      //TODO...
        void bellmanFordShortestPath(const T &s);   //TODO...
        vector<T> getPathTo(const T &dest) const;   //TODO...

        // Fp05 - all pairs
        void floydWarshallShortestPath();   //TODO...
        vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {

	for(auto vertex : vertexSet) {
	    vertex->dist = infinite;
	    vertex->path = NULL;
	}

	auto start = findVertex(orig);
	start->dist = 0;
	queue<Vertex<T>*> queue;
	queue.push(start);

	while(!queue.empty()) {
	    auto front = queue.front();
	    queue.pop();

	    for(auto edge : front->adj) {
	        auto elem = edge.dest;
	        if(elem->dist == infinite) {
	            elem->dist = front->dist + 1;
	            elem->path = front;
	            queue.push(elem);
	        }
	    }
	}
}

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	for(auto vertex : vertexSet) {
	    vertex->dist = infinite;
	    vertex->path = NULL;
	}

	auto start = findVertex(origin);
	start->dist = 0;

	MutablePriorityQueue<Vertex<T>> minQueue;
    minQueue.insert(start);

    while(!minQueue.empty()) {
        auto min = minQueue.extractMin();

        for(auto edge : min->adj) {
            auto elem = edge.dest;

            if(elem->dist > min->dist + edge.weight) {
                elem->dist = min->dist + edge.weight;
                elem->path = min;

                // if elem is not in queue
                if(elem->queueIndex == 0) { //old dist(w) was infinite
                    minQueue.insert(elem);
                }

                else {
                    minQueue.decreaseKey(elem);
                }
            }
        }
    }

}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
    for(auto vertex : vertexSet) {
        vertex->dist = infinite;
        vertex->path = NULL;
    }

    auto start = findVertex(orig);
    start->dist = 0;

    for(int i = 0; i < vertexSet.size() - 1; i++) {
        for(auto vertex : vertexSet) {
            for(auto edge : vertex->adj) {
                auto elem = edge.dest;
                if(elem->dist > vertex->dist + edge.weight) {
                    elem->dist = vertex->dist + edge.weight;
                    elem->path = vertex;
                }
            }
        }
    }

    for(auto vertex : vertexSet) {
        for(auto edge : vertex->adj) {
            auto elem = edge.dest;
            if(elem->dist > vertex->dist + edge.weight) {
                elem->dist = vertex->dist + edge.weight;
                elem->path = vertex;
            }
        }
    }

}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
    Vertex<T> *end = findVertex(dest);

    res.insert(res.begin(), end->info);

    while(end->path != NULL) {
        end = end->path;
        res.insert(res.begin(), end->info);
	}

	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
