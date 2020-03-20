/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited = false;  // auxiliary field used by dfs and bfs
	int indegree = 0;      // auxiliary field used by topsort
	bool processing = false;       // auxiliary field used by isDAG

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);
	friend class Graph<T>;
};

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
class Graph {
    private:
        vector<Vertex<T> *> vertexSet;    // vertex set
        void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
        Vertex<T> *findVertex(const T &in) const;
        bool dfsIsDAG(Vertex<T> *v) const;

    public:
        int getNumVertex() const;
        bool addVertex(const T &in);
        bool removeVertex(const T &in);
        bool addEdge(const T &sourc, const T &dest, double w);
        bool removeEdge(const T &sourc, const T &dest);
        vector<T> dfs() const;
        vector<T> bfs(const T &source) const;
        vector<T> topsort() const;
        int maxNewChildren(const T &source, T &inf) const;
        bool isDAG() const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
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
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if (findVertex(in) != NULL) {
        return false;
    }
    this->vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    Vertex<T> *src = findVertex(sourc);
    Vertex<T> *dst = findVertex(dest);

    if(src != NULL && dst != NULL) {
        src->addEdge(dst, w);
        return true;
    }
	return false;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	this->adj.push_back(Edge<T>(d, w));
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> *src = findVertex(sourc);
    Vertex<T> *dst = findVertex(dest);
    if(src != NULL & dst != NULL) {
        return src->removeEdgeTo(dst);
    }
	return false;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    for(auto it = this->adj.begin(); it<this->adj.end(); it++) {
        if(it->dest == d) {
            adj.erase(it);
            return true;
        }
    }
	return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    Vertex<T> *v = this->findVertex(in);
    if(v == NULL) {
        return false;
    }

    //Note: when you erase an iterator you cannot increment or decrement it
    for(auto it = this->vertexSet.begin(); it < this->vertexSet.end();) {
        if((*it)->info == in) {
            it = this->vertexSet.erase(it);
        }
        else {
            (*it)->removeEdgeTo(v);
            it++;
        }
    }
    return true;
}

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	vector<T> res;

    for(auto vertex : this->vertexSet) vertex->visited = false;

	for(auto vertex : this->vertexSet) {
	    if(!vertex->visited) {
	        this->dfsVisit(vertex, res);
	    }
	}

	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
	v->visited = true;
	res.push_back(v->info);

	for(auto edge : v->adj) {
	    if(!edge.dest->visited) {
	        dfsVisit(edge.dest, res);
	    }
	}
}

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    queue<Vertex<T>*> q;

    for(auto vertex : this->vertexSet) vertex->visited = false;

    q.push(this->vertexSet.at(0));
    this->vertexSet.at(0)->visited = true;

    while(!q.empty()) {
       auto next = q.front();
       q.pop();
       res.push_back(next->info);

       for(auto edge : next->adj) {
           if(!edge.dest->visited) {
               q.push(edge.dest);
               edge.dest->visited = true;
           }
       }
    }

    return res;
}

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
	vector<T> res;
	queue<Vertex<T>*> q;

    for(auto vertex : this->vertexSet) vertex->indegree = 0;

    // Calculates the intitial indegree for each vertice
	for(auto vertex : this->vertexSet) {
        for(auto edge : vertex->adj) {
            edge.dest->indegree++;
        }
    }

	// We start with vertices with indegree 0 and put them on the queue
	for(auto vertex : this->vertexSet) {
	    if(vertex->indegree == 0) {
	        q.push(vertex);
	    }
	}

    while(!q.empty()) {
        // we move the elements with indegree 0 and move them to the list(array)
        auto next = q.front();
        q.pop();
        res.push_back(next->info);

        // until the queue is not empty repeat the process
        // recalculate indegree for vertices linked with vertice next
        // after recalculating putting them on the queue again
        for(auto edge : next->adj) {
            edge.dest->indegree--;
            if(edge.dest->indegree == 0) {
                q.push(edge.dest);
            }
        }
    }
    //if the size of the of res list != number of vertices on the graph -> the graph has cicles
	return res.size() != vertexSet.size() ? vector<T>() : res;
}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
    vector<T> res;
    queue<Vertex<T>*> q;
    int max = 0;

    // Starts at the source
    auto vertex = findVertex(source);
    q.push(vertex);
    vertex->visited = true;

    while(!q.empty()) {
        auto next = q.front();
        q.pop();
        res.push_back(next->info);

        int maxCur = 0;
        for(auto edge : next->adj) {
            if(!edge.dest->visited) {
                q.push(edge.dest);
                edge.dest->visited = true;
                maxCur++;
            }
        }
        if(maxCur > max) {
            max = maxCur;
            inf = next->info;
        }
    }

    return max;
}

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
    for(auto vertex : this->vertexSet) {
        vertex->visited = false;
        vertex->processing = false;
    }
    return dfsIsDAG(vertexSet.at(0));
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	v->visited = true;

    for(auto edge : v->adj) {
        if(edge.dest->processing) return false;

        else if(!edge.dest->visited) {
            edge.dest->processing = true;
            if(!dfsIsDAG(edge.dest)) return false;
        }
    }
    return true;
}

#endif /* GRAPH_H_ */
