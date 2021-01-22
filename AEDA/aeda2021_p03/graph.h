#include <iostream>
#include <vector>

using namespace std;

template <class N, class E> class Edge;

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 */
template <class N, class E>
class Node {
public:
    N info;
    vector< Edge<N,E> > edges;
    Node(N inf) {
        info = inf;
    }
};

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 */
template <class N, class E>
class Edge {
public:
    E value;
    Node<N,E> *destination;
    Edge(Node<N,E> *dest, E val) {
        value = val;
        destination = dest;
    }
};

/**
 *
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 */
template <class N, class E>

class Graph {
    vector< Node<N,E> *> nodes;
public:
    Graph();
    ~Graph();
    Graph & addNode(const N &inf);
    Graph & addEdge(const N &begin, const N &end, const E &val);
    Graph & removeEdge(const N &begin, const N &end);
    E & edgeValue(const N &begin, const N &end);
    unsigned numEdges(void) const;
    unsigned numNodes(void) const;
    void print(std::ostream &os) const;
    template<class A, class B>
    friend ostream& operator<<(ostream& os, const Graph<A, B>& g);
};


/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 * @param out Stream you want to write to
 * @param g The graph you the information written from
 * @return
 */
template <class N, class E>
std::ostream & operator<<(std::ostream &out, const Graph<N,E> &g);


// exception NodeAlreadyExists
/**
 *
 * @tparam N Type of the information of what node already exists
 */
template <class N>
class NodeAlreadyExists
{
public:
    N info;
    NodeAlreadyExists(N inf) { info=inf; }
};

/**
 *
 * @tparam N Type of the exception's information
 * @param out Stream you want to write to
 * @param no object of the risen exception
 * @return
 */
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeAlreadyExists<N> &no)
{ out << "Node already exists: " << no.info; return out; }


// exception NodeDoesNotExist
/**
 *
 * @tparam N Type of the information of what node doesn't exist
 */
template <class N>
class NodeDoesNotExist {
public:
    N info;
    NodeDoesNotExist(N inf) {
        info = inf;
    }
};

/**
 *
 * @tparam N Type of the exception's information
 * @param out Stream you want to write to
 * @param no Object of the risen exception
 * @return Stream out
 */
template <class N>
std::ostream & operator<<(std::ostream &out, const NodeDoesNotExist<N> &no)
{ out << "Node does not exist: " << no.info; return out; }


/**
 *
 * @tparam N Type of the information of what Edge already exists
 */
template<class N>
class EdgeAlreadyExists{
public:
    N info;
    EdgeAlreadyExists(N beg, N end){
        info = beg + " , " + end;
    }
};

/**
 *
 * @tparam N Type of the node's information
 * @param out Stream you want to write to
 * @param no Object of the risen exception
 * @return Stream out
 */
template<class N>
ostream& operator<<(ostream& out, const EdgeAlreadyExists<N>& no){
    out << "Edge already exists: " << no.info;
    return out;
}

/**
 *
 * @tparam N Type of information of what edge doesn't exist
 */
template<class N>
class EdgeDoesNotExist{
public:
    N info;
    EdgeDoesNotExist(N beg, N end){
        info = beg + " , " + end;
    }
};

/**
 *
 * @tparam N Type of information of what edge doesn't exist
 * @param out Stream you want to write to
 * @param no Object of risen exception
 * @return Stream out
 */
template<class N>
ostream& operator<<(ostream& out, const EdgeDoesNotExist<N>& no){
    out << "Edge does not exist: " << no.info;
    return out;
}

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 */
template <class N, class E>
Graph<N, E>::Graph() {}

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 */
template <class N, class E>
Graph<N, E>::~Graph() {
    nodes.clear();
}

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 * @return Number of nodes in the graph
 */
template <class N, class E>
unsigned Graph<N, E>::numNodes() const {
    return nodes.size();
}

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 * @return Number of edges in the graph
 */
template <class N, class E>
unsigned Graph<N, E>::numEdges() const {
    unsigned num = 0;
    for (size_t i = 0; i < nodes.size(); ++i){
        num += nodes.at(i)->edges.size();
    }
    return num;
}

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 * @param inf Information of the node you want to add
 * @return Returns the same object (itself)
 */
template <class N, class E>
Graph<N, E>& Graph<N, E>::addNode(const N &inf) {
    for (size_t i = 0; i < nodes.size(); ++i){
        if (nodes.at(i)->info == inf) throw NodeAlreadyExists<N>(inf);
    }
    Node<N, E>* n = new Node<N, E>(inf);
    nodes.push_back(n);
    return *this;
}

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 * @param begin Information of the node in which the new edge begins
 * @param end Information of the node in which the new edge ends
 * @param val Value of the new edge
 * @return Returns the same object (itself)
 */
template <class N, class E>
Graph<N, E>& Graph<N, E>::addEdge(const N &begin, const N &end, const E &val) {
    Node<N, E>* endn;
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes.at(i)->info == end) {
            endn = nodes.at(i);
            break;
        }
        if (i == nodes.size() - 1) throw NodeDoesNotExist<N>(end);
    }
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes.at(i)->info == begin) {
            for (size_t j = 0; j < nodes.at(i)->edges.size(); ++j) {
                if (nodes.at(i)->edges.at(j).destination->info == end)
                    throw EdgeAlreadyExists<N>(begin, end);
            }
            Edge<N, E> e(endn, val);
            nodes.at(i)->edges.push_back(e);
            break;
        }
        if (i == nodes.size() - 1) throw NodeDoesNotExist<N>(begin);
    }
    return *this;
}

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 * @param begin Information of the node in which the edge we want begins
 * @param end Information of the node in which the edge we want ends
 * @return Returns the same object (itself)
 */
template <class N, class E>
E& Graph<N, E>::edgeValue(const N &begin, const N &end) {
    for (size_t i = 0; i < nodes.size(); ++i){
        if (nodes.at(i)->info == begin){
            for (size_t j = 0; j < nodes.at(i)->edges.size(); ++j){
                if (nodes.at(i)->edges.at(j).destination->info == end)
                    return nodes.at(i)->edges.at(j).value;
            }
            throw EdgeDoesNotExist<N>(begin, end);
        }
    }
    throw NodeDoesNotExist<N>(begin);
}

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 * @param begin Information of the node in which the edge we want to remove begins
 * @param end Information of the node in which the edge we want to remove ends
 * @return Returns the same object (itself)
 */
template <class N, class E>
Graph<N, E>& Graph<N, E>::removeEdge(const N &begin, const N &end) {
    for (size_t i = 0; i < nodes.size(); ++i){
        if (nodes.at(i)->info == begin){
            for (size_t j = 0; j < nodes.at(i)->edges.size(); ++j){
                if (nodes.at(i)->edges.at(j).destination->info == end) {
                    nodes.at(i)->edges.erase(nodes.at(i)->edges.begin() + j);
                    return *this;
                }
            }
            throw EdgeDoesNotExist<N>(begin, end);
        }
    }
    throw NodeDoesNotExist<N>(begin);
}

/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 * @param os The stream you want to write to
 */
template <class N, class E>
void Graph<N, E>::print(std::ostream &os) const {
    for (size_t i = 0; i < nodes.size(); ++i){
        os << "( " << nodes.at(i)->info;
        for (size_t j = 0; j < nodes.at(i)->edges.size(); ++j){
            os << "[ " << nodes.at(i)->edges.at(j).destination->info << " " << nodes.at(i)->edges.at(j).value << "] ";
        }
        os << ") ";
    }
}


/**
 *
 * @tparam N Type of the node's information
 * @tparam E Type of the edge's value
 * @param os The output stream you want to write to
 * @param g The graph you want the information written from
 * @return The output stream os
 */
template <class N, class E>
ostream& operator<<(ostream& os, const Graph<N, E>& g){
    for (size_t i = 0; i < g.nodes.size(); ++i){
        os << "( " << g.nodes.at(i)->info;
        for (size_t j = 0; j < g.nodes.at(i)->edges.size(); ++j){
            os << "[ " << g.nodes.at(i)->edges.at(j).destination->info << " " << g.nodes.at(i)->edges.at(j).value << "] ";
        }
        os << ") ";
    }
    return os;
}